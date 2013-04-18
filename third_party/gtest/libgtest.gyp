{
    'includes': [
        '../../support/common.gypi',
    ],
    'targets': [
    {
        'target_name': 'libgtest',
        'type': '<(component)',
        'sources': [
            'third_party/gtest/src/gtest-all.cc',
            'third_party/gtest/src/gtest_main.cc',
        ],
        'include_dirs': [
            'third_party/gtest/include',
            'third_party/gtest',
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
