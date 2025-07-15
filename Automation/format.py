import subprocess
import os

class Config:
    SOURCE_DIR_CORE = "C:\dev\Monitor\core"
    SOURCE_DIR_DESKTOP = "C:\dev\Monitor\gui_monitor_desktop"
    SOURCE_DIR_MOBA = "C:\dev\Monitor\gui_monitor_mobile"

def run_clang_format(source_dir):
    # Find all .cpp .h in the specified source directory
    format_sources = []
    for root, _, files in os.walk(source_dir):
        for file in files:
            if file.endswith('.cpp') or file.endswith('.h'):
                format_sources.append(os.path.join(root, file))

    if not format_sources:
        print(f'No source files found in {source_dir}.')
        return

    # Run clang-format command
    command = ['clang-format', '-i'] + format_sources
    result = subprocess.run(command)
    if result.returncode == 0:
        print(f'Clang-format successfully applied.')
    else:
        print(f'Error running clang-format.')

if __name__ == "__main__":
    run_clang_format(Config.SOURCE_DIR_CORE)
    run_clang_format(Config.SOURCE_DIR_DESKTOP)
    run_clang_format(Config.SOURCE_DIR_MOBA)