#include "circus_app.h"

#include <godot_cpp/classes/center_container.hpp>
#include <godot_cpp/classes/color_rect.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/panel_container.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/scroll_container.hpp>
#include <godot_cpp/classes/style_box_flat.hpp>
#include <godot_cpp/classes/theme.hpp>
#include <godot_cpp/classes/text_server.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

namespace {
// Global initialization must not call Godot's API before GDExtension initialization.
const Color cream(244.0f / 255, 234.0f / 255, 216.0f / 255);
const Color muted(183.0f / 255, 174.0f / 255, 190.0f / 255);
const Color gold(233.0f / 255, 185.0f / 255, 109.0f / 255);

Ref<StyleBoxFlat> box(Color color, Color border = Color("40394e")) {
    Ref<StyleBoxFlat> style;
    style.instantiate();
    style->set_bg_color(color);
    style->set_border_color(border);
    for (int i = 0; i < 4; ++i) {
        style->set_border_width(static_cast<Side>(i), 1);
        style->set_content_margin(static_cast<Side>(i), 16);
        style->set_corner_radius(static_cast<Corner>(i), 12);
    }
    return style;
}

Label* label(Node* parent, String text, int size = 20, Color color = cream) {
    auto* node = memnew(Label);
    node->set_text(text);
    node->set_horizontal_alignment(HORIZONTAL_ALIGNMENT_CENTER);
    node->set_autowrap_mode(TextServer::AUTOWRAP_WORD_SMART);
    node->add_theme_font_size_override("font_size", size);
    node->add_theme_color_override("font_color", color);
    parent->add_child(node);
    return node;
}

Button* button(Node* parent, String name, String text, bool primary = false) {
    auto* node = memnew(Button);
    node->set_name(name);
    node->set_text(text);
    node->set_custom_minimum_size(Vector2(0, 60));
    node->set_focus_mode(Control::FOCUS_ALL);
    if (primary) {
        node->add_theme_stylebox_override("normal", box(gold, gold));
        node->add_theme_stylebox_override("hover", box(Color("f3cd91"), gold));
        node->add_theme_stylebox_override("pressed", box(Color("c9904a"), gold));
        for (const auto* state : {"font_color", "font_hover_color", "font_pressed_color", "font_focus_color"}) {
            node->add_theme_color_override(state, Color("241d2c"));
        }
    }
    parent->add_child(node);
    return node;
}

VBoxContainer* page(Node* parent, String name) {
    auto* node = memnew(VBoxContainer);
    node->set_name(name);
    node->add_theme_constant_override("separation", 16);
    parent->add_child(node);
    return node;
}
} // namespace

void CircusApp::_bind_methods() {}

void CircusApp::_ready() {
    if (Engine::get_singleton()->is_editor_hint()) {
        return;
    }
    get_tree()->set_quit_on_go_back(false);
    Ref<Theme> theme;
    theme.instantiate();
    theme->set_default_font_size(20);
    theme->set_color("font_color", "Button", cream);
    theme->set_color("font_hover_color", "Button", cream);
    theme->set_color("font_pressed_color", "Button", cream);
    theme->set_color("font_disabled_color", "Button", Color("827889"));
    theme->set_stylebox("normal", "Button", box(Color("302839")));
    theme->set_stylebox("hover", "Button", box(Color("413448"), gold));
    theme->set_stylebox("pressed", "Button", box(Color("201b29"), gold));
    theme->set_stylebox("disabled", "Button", box(Color("211c29")));
    auto focus = box(Color(0, 0, 0, 0), gold);
    for (int i = 0; i < 4; ++i) focus->set_border_width(static_cast<Side>(i), 3);
    theme->set_stylebox("focus", "Button", focus);
    theme->set_stylebox("normal", "LineEdit", box(Color("18141e")));
    theme->set_stylebox("focus", "LineEdit", focus);
    theme->set_color("font_color", "LineEdit", cream);
    theme->set_color("caret_color", "LineEdit", gold);
    set_theme(theme);

    auto* background = memnew(ColorRect);
    add_child(background);
    background->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
    background->set_color(Color("17131e"));
    background->set_mouse_filter(MOUSE_FILTER_IGNORE);
    auto* margins = memnew(MarginContainer);
    add_child(margins);
    margins->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
    for (const auto* side : {"margin_left", "margin_right", "margin_top", "margin_bottom"}) {
        margins->add_theme_constant_override(side, 24);
    }
    auto* scroll = memnew(ScrollContainer);
    margins->add_child(scroll);
    scroll->set_horizontal_scroll_mode(ScrollContainer::SCROLL_MODE_DISABLED);
    scroll->set_follow_focus(true);
    auto* center = memnew(CenterContainer);
    scroll->add_child(center);
    center->set_h_size_flags(SIZE_EXPAND_FILL);
    center->set_v_size_flags(SIZE_EXPAND_FILL);
    content = page(center, "Content");
    content->add_theme_constant_override("separation", 24);
    label(content, "T H E   C I R C U S   L E D G E R", 16, gold);
    label(content, "Pathfinder Circus", 40);
    label(content, "A little order behind the extraordinary.", 18, muted);
    auto* panel = memnew(PanelContainer);
    content->add_child(panel);
    panel->add_theme_stylebox_override("panel", box(Color("241e2d")));
    auto* pages = page(panel, "Pages");

    menu = page(pages, "Menu");
    label(menu, "Welcome, showrunner", 26);
    label(menu, "Gather your troupe. Prepare the next show.", 18, muted);
    new_button = button(menu, "NewCircus", "New Circus", true);
    new_button->connect("pressed", callable_mp(this, &CircusApp::open_naming));
    resume_button = button(menu, "ResumeSession", "Return to current circus");
    resume_button->connect("pressed", callable_mp(this, &CircusApp::resume_session));
    auto* continue_button = button(menu, "Continue", "Continue");
    continue_button->set_disabled(true);
    label(menu, "No saved circus. Saving will be available in a future update.", 16, muted);
    if (!OS::get_singleton()->has_feature("android")) {
        button(menu, "Quit", "Quit")->connect("pressed", callable_mp(this, &CircusApp::quit));
    }

    naming = page(pages, "Naming");
    label(naming, "Every circus needs a name", 26);
    label(naming, "What will the posters say?", 18, muted);
    name_input = memnew(LineEdit);
    naming->add_child(name_input);
    name_input->set_name("CircusNameInput");
    name_input->set_placeholder("Circus of Wayward Wonders");
    name_input->set_max_length(64);
    name_input->set_custom_minimum_size(Vector2(0, 60));
    name_input->connect("text_submitted", callable_mp(this, &CircusApp::name_submitted));
    error_label = label(naming, "", 17, Color("ffaaa0"));
    error_label->set_name("NameError");
    label(naming, "This circus stays in memory until you close the app. Creating a new one replaces the current session.", 16, muted);
    create_button = button(naming, "CreateCircus", "Create Circus", true);
    create_button->connect("pressed", callable_mp(this, &CircusApp::create_circus));
    button(naming, "Cancel", "Back to menu")->connect("pressed", callable_mp(this, &CircusApp::go_back));

    overview = page(pages, "Overview");
    label(overview, "YOUR CIRCUS", 16, gold);
    circus_name = label(overview, "", 28);
    circus_name->set_name("CircusName");
    stats = label(overview, "", 21);
    stats->set_name("CircusStats");
    label(overview, "The stage is yours. Circus management, money, and shows are coming next.", 18, muted);
    for (const auto* text : {"Actors & tricks", "Money & upgrades", "Prepare a show"}) {
        auto* pending = button(overview, String(text).replace(" ", ""), String(text) + "  (coming soon)");
        pending->set_disabled(true);
    }
    back_button = button(overview, "BackToMenu", "Back to menu", true);
    back_button->connect("pressed", callable_mp(this, &CircusApp::go_back));
    label(content, "A companion for the game master", 15, muted);
    connect("resized", callable_mp(this, &CircusApp::resize_content));
    resize_content();
    show_screen(Screen::Menu);
}

void CircusApp::resize_content() {
    if (content) content->set_custom_minimum_size(Vector2(MAX(240.0, MIN(620.0, get_size().x - 56.0)), 0));
}

void CircusApp::show_screen(Screen next) {
    screen = next;
    menu->set_visible(next == Screen::Menu);
    naming->set_visible(next == Screen::Naming);
    overview->set_visible(next == Screen::Overview);
    resume_button->set_visible(session.has_value());
    if (next == Screen::Menu) new_button->grab_focus();
    else if (next == Screen::Naming) name_input->grab_focus();
    else back_button->grab_focus();
}

void CircusApp::open_naming() {
    name_input->clear();
    error_label->set_text("");
    show_screen(Screen::Naming);
}

void CircusApp::resume_session() {
    if (session) show_screen(Screen::Overview);
}

void CircusApp::create_circus() {
    const String name = name_input->get_text().strip_edges();
    if (name.is_empty()) {
        error_label->set_text("Please enter a circus name.");
        name_input->grab_focus();
        return;
    }
    session.emplace();
    session->name = name.utf8().get_data();
    circus_name->set_text(String::utf8(session->name.c_str()));
    stats->set_text("Prestige  " + String::num_int64(circus::calculate_prestige(*session).total()) +
                   "     |     Balance  " + String::num_int64(session->balance.copper) + " cp\n" +
                   String::num_int64(session->actors.size()) + " actors   /   " +
                   String::num_int64(session->show_history.size()) + " shows");
    show_screen(Screen::Overview);
}

void CircusApp::name_submitted(const String&) { create_circus(); }
void CircusApp::go_back() {
    if (screen != Screen::Menu) show_screen(Screen::Menu);
    else if (OS::get_singleton()->has_feature("android")) quit();
}
void CircusApp::quit() { get_tree()->quit(); }
void CircusApp::_notification(int what) {
    if (what == NOTIFICATION_WM_GO_BACK_REQUEST && menu) go_back();
}
void CircusApp::_input(const Ref<InputEvent>& event) {
    Ref<InputEventKey> key = event;
    if (key.is_valid() && key->is_pressed() && !key->is_echo() && key->get_keycode() == KEY_ESCAPE) {
        go_back();
        get_viewport()->set_input_as_handled();
    }
}
