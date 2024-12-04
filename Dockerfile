# Use a lightweight Debian image
FROM debian:bullseye-slim

# Install necessary tools
RUN apt-get update && apt-get install -y \
    gcc make gdb \
    && apt-get clean

# Set the working directory inside the container
WORKDIR /app