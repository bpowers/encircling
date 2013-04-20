#-*- mode: python -*-
{
    'includes': [
        'support/common.gypi',
    ],
    'targets': [
    {
        'target_name': 'libencircling',
        'type': '<(component)',
        'sources': [
            'src/array.cc',
            'src/slice.cc',
            'src/string.cc',
        ],
        'include_dirs': [
            'include',
        ],
    },
    {
        'target_name': 'test_encircling',
        'type': 'executable',
        'sources': [
            'tests/all.cc',
        ],
        'dependencies': [
            'libencircling',
            'third_party/gtest/libgtest.gyp:*',
        ],
        'include_dirs': [
            'third_party/gtest/include',
            'include',
        ],
        'cflags!': [
            '-Wundef',
        ],
        'cflags': [
            '-Wno-undef',
            '-Wno-missing-noreturn',
        ],
    },
    ],
}
