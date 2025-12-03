class File:
    """
    Write to file as usual.
    """

    def __init__(self, file_name) -> None:
        self.file_name = file_name

    def write(self, bytes: bytearray):
        """Write bytes to file immediately"""
        with open(self.file_name, 'ab') as fp:  # A-ppend B-ytes to existing file
            fp.write(bytes)


class BufferedFile(File):
    """
    Write data to file, using an additional memory buffer to reduce disk writes.

    Example Usage:
    ```
        bf = BufferedFile(File("test.log"), buffer_size=4)
        bf.write(bytearray(b'12345678'))
    ```
    """


    def __init__(self, file: File, buffer_size: int):
        self.buffer_size = buffer_size
        self.file = file
        self.buffer = bytearray()


    def write(self, bytes: bytearray):
        """
        write the data that has space
        track what was written
        flush if needed
        """
        
        bytes_ptr = 0
        
        while len(bytes) > bytes_ptr:
            bytes_to_write = min(len(bytes)-bytes_ptr, self.buffer_size - len(self.buffer))

            self.buffer.extend(bytes[bytes_ptr: bytes_ptr+bytes_to_write])
            if len(self.buffer) >= self.buffer_size:
                self.flush()

            bytes_ptr = bytes_ptr + bytes_to_write

    def flush(self):
        if self.buffer:
            self.file.write(self.buffer)
            self.buffer = bytearray()


bf = BufferedFile(File("test.log"), 4)
bf.write(bytearray(b'12345678'))
