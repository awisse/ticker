# Prepare .desktop file

desktop_in = configure_file(
  input: '@0@.desktop.in.in'.format(base_id),
  output: '@BASENAME@',
  configuration: {'app_id': app_id}
)

desktop_file = i18n.merge_file(
        input: desktop_in,
       output: '@BASENAME@',
         type: 'desktop',
       po_dir: '../po',
      install: true,
  install_dir: get_option('datadir') / 'applications'
)

desktop_utils = find_program('desktop-file-validate', required: false)
if desktop_utils.found()
  test('Validate desktop file', desktop_utils, args: [desktop_file])
endif

# Prepare .gschema file

gschema_file = configure_file(
  input: '@0@.gschema.xml.in'.format(base_id),
  output: '@BASENAME@',
  configuration: {'base_id': base_id,
                  'resource_base_path': resource_base_path}
)

# Prepare .metainfo file
metainfo_in = configure_file(
  input: 'ca.awisse.ticker.metainfo.xml.in.in',
  output: '@BASENAME@',
  configuration: {'app_id': app_id, 'build_type': profile}
)

appstream_file = i18n.merge_file(
        input: metainfo_in,
       output: '@BASENAME@',
       po_dir: '../po',
      install: true,
  install_dir: get_option('datadir') / 'metainfo'
)

appstreamcli = find_program('appstreamcli', required: false, disabler: true)
test('Validate appstream file', appstreamcli,
     args: ['validate', '--no-net', '--explain', appstream_file])

install_data(gschema_file,
  install_dir: get_option('datadir') / 'glib-2.0' / 'schemas'
)

compile_schemas = find_program('glib-compile-schemas', required: false, disabler: true)
test('Validate schema file',
     compile_schemas,
     args: ['--strict', '--dry-run', meson.current_source_dir()])

subdir('icons')
