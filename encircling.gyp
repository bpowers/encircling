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
    ],
}
