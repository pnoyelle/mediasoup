obuparse_sources = [
  'obuparse/obuparse.c',
  'obuparse/obuparse.h',
  'obuparse/tools/json.c',
  'obuparse/tools/json.h',
]

local_include_directories = declare_dependency(
  include_directories: include_directories('obuparse')
)

obuparse = library(
  'obuparse',
  obuparse_sources,
  dependencies: [
    local_include_directories,
  ],
  include_directories: obuparse_include_directories,
  cpp_args: cpp_args,
)

obuparse_dep = declare_dependency(
  dependencies: [
    local_include_directories,
  ],
  include_directories: include_directories('.'),
  link_with: obuparse,
)