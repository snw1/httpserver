#HTTPServer

A simple Linux/Windows HTTP server, written for educational purposes.
Written in pure C++11, no libraries or 3rd party code used.

##Main Features

* Cross-platform: Linux and Windows supported
* Multithreaded, single proceess
* Up to 1000 concurrent requests support
* Supported HTTP response codes:
    * 200
    * 404
* Supported MIME types:
    * image/bmp
    * image/jpeg
    * image/png
    * image/gif
    * application/pdf
    * text/html
    * text/plain
    * audio/mpeg
    * video/mp4
    * application/octet-stream
* Directory listing supported
* Support of non alphanumeric URIs
* High performance:
    * 10K local queries per second in a single thread
    * 22K local queries per second in multiple threads

##Copyright

Licensed under the [GPL](http://www.gnu.org/licenses/gpl.txt) license

##Authors

Andrew Sheetov <[andrew.sheetov@gmail.com](mailto:andrew.sheetov@gmail.com)> 2014
