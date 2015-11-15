"""Verilog rules for Bazel."""

V_FILETYPE = FileType([".v"])

_iverilog_bin = "/home/brian/.build/iverilog/build-install/bin/iverilog"
_vvp_bin = "/home/brian/.build/iverilog/build-install/bin/vvp"

def _v_binary_impl(ctx):
  v_binary = ctx.outputs.executable
  vvp = ctx.new_file(ctx.configuration.bin_dir,
                     "%s.vvp" % v_binary.basename)

  src_list = [src.path for src in ctx.files.srcs]
  cmd = [_iverilog_bin + " -o " + vvp.path + " " + " ".join(src_list)]
  ctx.action(
      inputs = ctx.files.srcs,
      outputs = [vvp],
      command = "\n".join(cmd),
      use_default_shell_env = True,
      progress_message = "iverilog %s" % ctx.label.name)

  ctx.file_action(
      output = v_binary,
      content = " ".join([
          "#!/bin/bash\n",
          "set -e\n",
          "%s -n %s\n" % (_vvp_bin, vvp.short_path)]),
      executable = True)

  runfiles = ctx.runfiles(files = [vvp], collect_data = True)
  return struct(runfiles = runfiles)

v_binary = rule(
    _v_binary_impl,
    executable = True,
    attrs = {
        "srcs" : attr.label_list(allow_files = V_FILETYPE),
    },
)
