newbuilder_sources = [
  'main.c',
  'newbuilder-window.c',
]

newbuilder_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
]

gnome = import('gnome')

newbuilder_sources += gnome.compile_resources('newbuilder-resources',
  'newbuilder.gresource.xml',
  c_name: 'newbuilder'
)

executable('newbuilder', newbuilder_sources,
  dependencies: newbuilder_deps,
  install: true,
)
