extends SceneTree

func _initialize() -> void:
	call_deferred("run")

func capture(path: String) -> void:
	await create_timer(0.25).timeout
	await RenderingServer.frame_post_draw
	var result = root.get_texture().get_image().save_png(path)
	if result != OK:
		push_error("Screenshot failed: " + path)
		quit(1)

func run() -> void:
	var app = load("res://scenes/main.tscn").instantiate()
	root.add_child(app)
	await capture("res://build/menu.png")
	app.find_child("NewCircus", true, false).pressed.emit()
	await capture("res://build/naming.png")
	app.find_child("CircusNameInput", true, false).text = "Circus of Wayward Wonders"
	app.find_child("CreateCircus", true, false).pressed.emit()
	await capture("res://build/overview.png")
	root.size = Vector2i(600, 960)
	await capture("res://build/overview-portrait.png")
	app.queue_free()
	await process_frame
	quit()
