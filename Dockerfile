FROM infinitecoding/platformio-for-ci

COPY platformio.ini .
COPY src/ data/ ./
