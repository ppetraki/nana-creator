pugixml_lib = static_library('pugixml',
  files('''
  pugixml/pugiconfig.hpp
  pugixml/pugixml.cpp
  pugixml/pugixml.hpp
    '''.split()),
  cpp_args:cpp_flags
  )

pugixml_dep = declare_dependency(
  link_with: pugixml_lib,
  include_directories: include_directories('.')
  )
