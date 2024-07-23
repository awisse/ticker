ticker_sources = [
  'main.c',
  'ticker-application.c',
  'ticker-window.c',
  'ticker-button.c',
  'ticking.c',
  'time-label.c'
]

ticker_deps = [
  dependency('gtk4')
]

ticker_sources += gnome.compile_resources('ticker-resources',
  'ticker.gresource.xml',
  c_name: 'ticker',
  source_dir: [data_dir]
)

executable('ticker', ticker_sources,
  dependencies: ticker_deps,
       install: true,
)
