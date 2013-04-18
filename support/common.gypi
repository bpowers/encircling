{
    'variables': {
        'variables': {
            # Compute the architecture that we're building on.
            'conditions': [
                ['OS=="win" or OS=="mac" or OS=="ios"', {
                    'host_arch%': 'ia32',
                }, {
                    # This handles the Unix platforms for which there is some support.
                    # Anything else gets passed through, which probably won't work
                    # very well; such hosts should pass an explicit target_arch to
                    # gyp.
                    'host_arch%':
                        '<!(uname -m | sed -e "s/i.86/ia32/;s/x86_64/x64/;s/amd64/x64/;s/arm.*/arm/;s/i86pc/ia32/")',
                }],
            ],
        },

        'clang%': 0,
        'profile%': 0,

        'host_arch%': '<(host_arch)',

        # Default architecture we're building for is the architecture we're
        # building on.
        'target_arch%': '<(host_arch)',

        # By default, component is set to static_library and it can be overriden
        # by the GYP command line or by ~/.gyp/include.gypi.
        'component%': 'static_library',
    },
    'target_defaults': {
        'conditions': [
            ['OS=="win"', {
                'defines': [
                    'WIN32=1'
                ],
                'msvs_settings': {
                    'VCCLCompilerTool': {
                        'ExceptionHandling': '2',  # /EHsc
                    },
                },
            }, { # OS != "win"
                'cflags': [
                    '--std=c++11',
                    '-g',
                    '-O0',
                    '-Wall',
                    '-Wextra',
                    '-Wformat',
                    '-Wundef',
                    '-Wpointer-arith',
                    '-Wcast-qual',
                    '-Wwrite-strings',
                    '-Wsign-compare',
                    '-Wmissing-noreturn',
                    '-Wstrict-aliasing=2',
                    #'-Wno-unused-local-typedefs',
                    '-Wno-unused-parameter',
                    '-Wno-unused-function',
                    '-Wno-unknown-pragmas',
                    '-Wno-parentheses',
		    #'-Wno-suggest-attribute=noreturn',
                    '-Wno-invalid-offsetof', # FIXME - fix
                    '-Wno-switch', # FIXME - fix
                    '-fPIC',
                ],
                'libraries': [
                    '-lpthread',
                    '-ldl',
                ],
                'conditions': [
                    ['profile==1', {
                        'cflags': [
                            '-ftest-coverage',
                            '-fprofile-arcs',
                        ],
                        'link_settings': {
                            'ldflags': [
                                '-ftest-coverage',
                                '-fprofile-arcs',
                            ],
                        },
                    }],
                ],
            }],

            ['clang==1', {
                'make_global_settings': [
                    ['CC', 'clang'],
                    ['CXX', 'clang++'],
                    ['LINK', '$(CXX)'],
                    ['CC.host', '$(CC)'],
                    ['CXX.host', '$(CXX)'],
                    ['LINK.host', '$(LINK)'],
                ],
                'cflags': [
                    '-fcolor-diagnostics',
                    '-Wno-invalid-source-encoding',
                ],
            }],
        ],

    },
}
