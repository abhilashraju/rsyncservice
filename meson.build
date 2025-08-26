
# Define the executable
project('rsyncservice', 'cpp',default_options: ['c_std=c18','cpp_std=c++23','cpp_args=-Wno-subobject-linkage'])
reactor_dep=dependency('reactor')
boost_dep = dependency('boost', modules: ['url'], required: true)
openssl_dep = dependency('openssl', required: true)
sdeventplus_dep = dependency('sdeventplus')
sdbusplus_dep =dependency('sdbusplus')

executable('rsyncservice',
  'rsyncservice.cpp',
  dependencies: [reactor_dep,sdbusplus_dep,sdeventplus_dep,openssl_dep,boost_dep],
  cpp_args: ['-DBOOST_ASIO_DISABLE_THREADS'],
  install: true,
  install_dir: '/usr/bin'
)
