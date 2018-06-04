# HTTPServer

A simple Linux/Windows/MacOS HTTP server, written for educational purposes.
Written in pure C++11, no libraries or 3rd party code used.

## Main Features

* Cross-platform: Linux, Windows and MacOS supported
* Multithreaded, single process
* Up to 1000 concurrent requests support
* Supported HTTP request types:
    * GET
* Supported HTTP response types:
    * 200 (OK)
    * 404 (Not Found)
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
* Performance:
    * 10K local queries per second in a single thread
    * 22K local queries per second in multiple threads

## Copyright

Licensed under the [GPL](http://www.gnu.org/licenses/gpl.txt) license

## Authors

Andrew Sheetov <[andrew.sheetov@gmail.com](mailto:andrew.sheetov@gmail.com)> 2014
