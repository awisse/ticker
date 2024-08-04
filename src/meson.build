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

# Resources

res_in = configure_file(
  input: 'ticker.gresource.xml.in',
  output: 'ticker.gresource.xml',
  configuration: src_conf
)


res = gnome.compile_resources(
  'ticker-resources',
  res_in,
  c_name: 'ticker',
  source_dir: [data_dir]
)

executable('ticker', ticker_sources + res,
  dependencies: ticker_deps,
       install: true,
)
