ticker_sources = [
  'main.c',
  'ticker-application.c',
  'ticker-window.c',
  'ticker-button.c',
]

ticker_deps = [
  dependency('gtk4'),
]

ticker_sources += gnome.compile_resources('ticker-resources',
  'ticker.gresource.xml',
  c_name: 'ticker'
)

executable('ticker', ticker_sources,
  dependencies: ticker_deps,
       install: true,
)
