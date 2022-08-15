Import("env")
import os

def copy_gzip_data(source, target, env):
  data = env.get("PROJECT_DATA_DIR")
  with open(os.path.join(data, 'VERSION'), 'w') as file:
    file.write(os.getenv('VERSION', "dev"))

env.AddPreAction("$BUILD_DIR/spiffs.bin", copy_gzip_data)