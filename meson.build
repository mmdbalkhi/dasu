project('dasu', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

pam_dep = dependency('pam', required: true)
pam_misc_dep = dependency('pam_misc', required: true)

exe = executable('dasu', 'dasu.c',
     dependencies: [pam_dep, pam_misc_dep],
     install : true,
)
