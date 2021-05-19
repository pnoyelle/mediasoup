{
  'targets':
  [
    {
      'target_name': 'obuparse',
      'type': 'static_library',
      'sources':
      [
        'obuparse/obuparse.c',
        'obuparse/obuparse.h',
        'obuparse/tools/json.c',
        'obuparse/tools/json.h',
      ],
      'direct_dependent_settings':
      {
        'include_dirs':
        [
          'obuparse'
        ]
      },
      'conditions':
      [
        [ 'OS != "win"', {
          'cflags': [ '-Wall', '-Wno-sign-compare' ]
        }],
        [ 'OS == "mac"', {
          'xcode_settings':
          {
            'WARNING_CFLAGS': [ '-Wall', '-Wno-sign-compare' ]
          }
        }]
      ]
    }
  ]
}
