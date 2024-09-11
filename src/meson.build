ticker_sources = [
  'main.c',
  'ticker-application.c',
  'ticker-window.c',
  'ticker-button.c',
  'click.c',
  'ttimer.c',
  'time-str.c'
]

ticker_deps = [
  dependency('gtk4')
]

# Configuration

src_conf = configuration_data()
src_conf.set('app_id', app_id)
src_conf.set('resource_base_path', resource_base_path)

# Builder

if get_option('profile') == 'devel'
  window_style = '<style><class name="devel" /></style>'
else
  window_style = ''
endif
conf_ui = {'window_style' : window_style}
configure_file(
  input: 'ticker-window.ui.in',
  output: '@BASENAME@',
  configuration: conf_ui
)

# Resources

gresources = configure_file(
  input: 'ticker.gresource.xml.in',
  output: '@BASENAME@',
  configuration: src_conf
)


resources = gnome.compile_resources(
  'ticker-resources',
  gresources,
  c_name: 'ticker',
  source_dir: [data_dir, meson.current_build_dir()]
)

executable('ticker', ticker_sources + resources,
  dependencies: ticker_deps,
       install: true,
)
