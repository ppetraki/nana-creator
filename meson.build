project('nana-creator',
    'cpp',
    version : '1.0.0',
    default_options : ['warning_level=3',  'cpp_std=c++17']
    )

cpp_flags  = []
link_flags = []

cpp = meson.get_compiler('cpp')
add_project_arguments(cpp.get_supported_arguments(cpp_flags), language : 'cpp')
add_project_link_arguments(cpp.get_supported_link_arguments(link_flags), language : 'cpp')


pugixml_lib = static_library('pugixml',
  files('''
  libs/pugixml/pugiconfig.hpp
  libs/pugixml/pugixml.cpp
  libs/pugixml/pugixml.hpp
    '''.split()),
  cpp_args:cpp_flags)

# this directory structure should be turned around
pugixml_dep = declare_dependency(
  link_with: pugixml_lib,
  include_directories: include_directories('libs')
  )

nana_dep  = dependency('nana')

include_dirs = include_directories('src')

executable('nana-creator',
  files('''
  src/assetspanel.cpp
  src/assetspanel.h
  src/codegenerator.cpp
  src/codegenerator_data.h
  src/codegenerator.h
  src/config.h
  src/creator.cpp
  src/creator.h
  src/ctrls/box_model.cpp
  src/ctrls/box_model.h
  src/ctrls/button.cpp
  src/ctrls/button.h
  src/ctrls/categorize.cpp
  src/ctrls/categorize.h
  src/ctrls/checkbox.cpp
  src/ctrls/checkbox.h
  src/ctrls/combox.cpp
  src/ctrls/combox.h
  src/ctrls/ctrl.cpp
  src/ctrls/ctrl.h
  src/ctrls/custom.cpp
  src/ctrls/custom.h
  src/ctrls/date_chooser.cpp
  src/ctrls/date_chooser.h
  src/ctrls/field.cpp
  src/ctrls/field.h
  src/ctrls/form.cpp
  src/ctrls/form.h
  src/ctrls/group.cpp
  src/ctrls/group.h
  src/ctrls/label.cpp
  src/ctrls/label.h
  src/ctrls/listbox.cpp
  src/ctrls/listbox.h
  src/ctrls/menubar.cpp
  src/ctrls/menubar.h
  src/ctrls/notebook.cpp
  src/ctrls/notebook.h
  src/ctrls/page.cpp
  src/ctrls/page.h
  src/ctrls/panel.cpp
  src/ctrls/panel.h
  src/ctrls/picture.cpp
  src/ctrls/picture.h
  src/ctrls/progress.cpp
  src/ctrls/progress.h
  src/ctrls/property.cpp
  src/ctrls/property.h
  src/ctrls/slider.cpp
  src/ctrls/slider.h
  src/ctrls/spinbox.cpp
  src/ctrls/spinbox.h
  src/ctrls/splitterbar.cpp
  src/ctrls/splitterbar.h
  src/ctrls/tabbar.cpp
  src/ctrls/tabbar.h
  src/ctrls/textbox.cpp
  src/ctrls/textbox.h
  src/ctrls/toolbar.cpp
  src/ctrls/toolbar.h
  src/ctrls/treebox.cpp
  src/ctrls/treebox.h
  src/filemanager.cpp
  src/filemanager.h
  src/guimanager.cpp
  src/guimanager.h
  src/imagemanager.cpp
  src/imagemanager.h
  src/info.cpp
  src/info.h
  src/inifile.cpp
  src/inifile.h
  src/items_dialog.cpp
  src/items_dialog.h
  src/lock_guard.h
  src/main.cpp
  src/namemanager.cpp
  src/namemanager.h
  src/nana_extra/color_helper.cpp
  src/nana_extra/color_helper.h
  src/nana_extra/pgitems.cpp
  src/nana_extra/pgitems.h
  src/nana_extra/propertygrid.cpp
  src/nana_extra/propertygrid.h
  src/new_project.cpp
  src/new_project.h
  src/objectspanel.cpp
  src/objectspanel.h
  src/pgitems_creator.cpp
  src/pgitems_creator.h
  src/propertiespanel.cpp
  src/propertiespanel.h
  src/propertygrid_helper.cpp
  src/propertygrid_helper.h
  src/scrollablecanvas.cpp
  src/scrollablecanvas.h
  src/style.h
  src/tree.h
  '''.split()),
  include_directories: include_dirs,
  dependencies: [pugixml_dep, nana_dep]
  )
