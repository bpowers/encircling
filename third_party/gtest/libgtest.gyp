#-*- mode: python -*-
{
    'includes': [
        '../../support/common.gypi',
    ],
    'targets': [
    {
        'target_name': 'libgtest',
        'type': '<(component)',
        'sources': [
            'src/gtest-all.cc',
            'src/gtest_main.cc',
        ],
        'include_dirs': [
            'include',
            '.',
        ],
        'conditions': [
            ['OS!="win"', {
                'cflags!': [
                    '-Wundef',
                ],
                'ldflags': [
                    '-lpthread',
                ],
            }],
        ],
    },
    ],
}
