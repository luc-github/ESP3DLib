import shutil
shutil.rmtree("Marlin/.pio/libdeps/esp32/ESP3DLib/")
shutil.copytree("../src", "Marlin/.pio/libdeps/esp32/ESP3DLib/")
print("Update ESP3DLib files")
