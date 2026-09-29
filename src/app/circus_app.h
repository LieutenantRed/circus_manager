#pragma once

#include "domain/circus.h"
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/input_event.hpp>

class CircusApp : public godot::Control {
    GDCLASS(CircusApp, godot::Control)

    enum class Screen { Menu, Naming, Overview };
    Screen screen = Screen::Menu;
    std::optional<circus::Circus> session;
    godot::VBoxContainer* content = nullptr;
    godot::VBoxContainer* menu = nullptr;
    godot::VBoxContainer* naming = nullptr;
    godot::VBoxContainer* overview = nullptr;
    godot::Button* new_button = nullptr;
    godot::Button* resume_button = nullptr;
    godot::Button* back_button = nullptr;
    godot::Button* create_button = nullptr;
    godot::LineEdit* name_input = nullptr;
    godot::Label* error_label = nullptr;
    godot::Label* circus_name = nullptr;
    godot::Label* stats = nullptr;

    void show_screen(Screen next);
    void open_naming();
    void resume_session();
    void create_circus();
    void name_submitted(const godot::String& text);
    void go_back();
    void quit();
    void resize_content();

protected:
    static void _bind_methods();
    void _notification(int what);

public:
    void _ready() override;
    void _input(const godot::Ref<godot::InputEvent>& event) override;
};
