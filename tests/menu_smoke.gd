extends SceneTree

var failures: Array[String] = []

func check(condition: bool, message: String) -> void:
	if not condition:
		failures.append(message)
		push_error(message)

func _initialize() -> void:
	call_deferred("run")

func run() -> void:
	var scene = load("res://scenes/main.tscn") as PackedScene
	if scene == null:
		quit(1)
		return
	var app = scene.instantiate()
	root.add_child(app)
	await process_frame
	await process_frame
	var menu = app.find_child("Menu", true, false)
	var naming = app.find_child("Naming", true, false)
	var overview = app.find_child("Overview", true, false)
	check(menu != null and app.is_class("CircusApp"), "Native C++ app must load")
	if menu == null:
		quit(1)
		return
	var new_button = app.find_child("NewCircus", true, false)
	var name_input = app.find_child("CircusNameInput", true, false)
	var create = app.find_child("CreateCircus", true, false)
	check(menu.visible and not naming.visible and not overview.visible, "Start at menu")
	check(app.find_child("Continue", true, false).disabled, "Continue remains disabled without persistence")
	check(not app.find_child("ResumeSession", true, false).visible, "No resume before creation")
	for pressed in [true, false]:
		var click = InputEventMouseButton.new()
		click.button_index = MOUSE_BUTTON_LEFT
		click.position = root.get_final_transform() * new_button.get_global_rect().get_center()
		click.global_position = click.position
		click.pressed = pressed
		Input.parse_input_event(click)
	await process_frame
	check(naming.visible and name_input.has_focus(), "New Circus opens focused naming form")
	name_input.text = "   "
	create.pressed.emit()
	check(naming.visible and not app.find_child("NameError", true, false).text.is_empty(), "Reject whitespace names")
	name_input.text = "  Цирк Étoile  "
	name_input.text_submitted.emit(name_input.text)
	check(overview.visible, "Enter submits and opens overview")
	check(app.find_child("CircusName", true, false).text == "Цирк Étoile", "Trim names and preserve Unicode")
	var stats: String = app.find_child("CircusStats", true, false).text
	check(stats.contains("Prestige  1") and stats.contains("Balance  0 cp"), "Overview reads initial C++ model values")
	app.notification(Node.NOTIFICATION_WM_GO_BACK_REQUEST)
	check(menu.visible, "Platform Back returns from overview to menu")
	app.find_child("ResumeSession", true, false).pressed.emit()
	check(overview.visible, "Return to current circus preserves session")
	app.find_child("BackToMenu", true, false).pressed.emit()
	new_button.pressed.emit()
	name_input.text = "Cancelled"
	var escape = InputEventKey.new()
	escape.keycode = KEY_ESCAPE
	escape.pressed = true
	Input.parse_input_event(escape)
	await process_frame
	check(menu.visible, "Escape cancels naming")
	app.find_child("ResumeSession", true, false).pressed.emit()
	check(app.find_child("CircusName", true, false).text == "Цирк Étoile", "Cancellation preserves original circus")
	app.find_child("BackToMenu", true, false).pressed.emit()
	new_button.pressed.emit()
	name_input.text = "Second Circus"
	create.pressed.emit()
	check(app.find_child("CircusName", true, false).text == "Second Circus", "Creating again replaces session")
	for dimensions in [Vector2i(1152, 864), Vector2i(800, 600), Vector2i(600, 960)]:
		root.size = dimensions
		await process_frame
		await process_frame
		check(app.find_child("Content", true, false).size.x <= app.size.x, "Content fits viewport width")
		check(app.find_child("BackToMenu", true, false).size.y >= 60, "Touch target remains large")
	app.queue_free()
	await process_frame
	print("Menu smoke test: ", "PASS" if failures.is_empty() else "FAIL")
	quit(0 if failures.is_empty() else 1)
