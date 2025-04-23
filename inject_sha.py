# inject_sha.py
#
# PRE-extra_script to force PlatformIO’s ElfToBin (elf2image)
# to include the ELF SHA256 at offset 0xb0. Without this, espcoredump.py
# will reject core dumps, as the SHA256 is not present in the firmware image.

Import("env")

def patch_elf_to_bin(env):
    # Locate the ElfToBin builder
    bld = env.get("BUILDERS", {}).get("ElfToBin")
    if not bld:
        return

    # Get the underlying Action
    action = bld.action
    # Some versions wrap the Action in a list
    actions = action if isinstance(action, list) else [action]

    for act in actions:
        try:
            cmd = list(act.get_builder_action().cmd_list)
        except AttributeError:
            continue  # Not a simple Action, skip

        # Only patch if not already present
        if "--elf-sha256-offset" not in cmd:
            # Find the elf2image invocation and insert our flag
            for i, part in enumerate(cmd):
                if "elf2image" in part:
                    cmd.insert(i + 1, "0xb0")
                    cmd.insert(i + 1, "--elf-sha256-offset")
                    break
            # Update the action’s command list
            act.get_builder_action().cmd_list = cmd

    # Re-assign patched action(s) back to the builder
    bld.action = actions if len(actions) > 1 else actions[0]

patch_elf_to_bin(env)
