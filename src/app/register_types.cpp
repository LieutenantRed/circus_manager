#include "circus_app.h"
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_circus(ModuleInitializationLevel level) {
    if (level == MODULE_INITIALIZATION_LEVEL_SCENE) ClassDB::register_class<CircusApp>();
}
void uninitialize_circus(ModuleInitializationLevel) {}

extern "C" {
GDExtensionBool GDE_EXPORT circus_library_init(
    GDExtensionInterfaceGetProcAddress get_proc_address,
    GDExtensionClassLibraryPtr library, GDExtensionInitialization* initialization) {
    GDExtensionBinding::InitObject init(get_proc_address, library, initialization);
    init.register_initializer(initialize_circus);
    init.register_terminator(uninitialize_circus);
    init.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
    return init.init();
}
}
