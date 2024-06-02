# srcstats

[live demo](https://srvstats.barpos.net/)

### Instalation
`git clone https://github.com/BarPos/srvstats`
`cd srvstats`
`mkdir out`
`cd out`
`cmake ..`
`cmake --build .`

### Add to systemd
Create a service at `/etc/systemd/system/srvstats.service`
```
[Unit]
Description=srvstats
After=network.target

[Service]
Type=exec
Restart=always
RestartSec=1
ExecStart=(path to the instalation)/out/srvstats

[Install]
WantedBy=multi-user.target
```
`systemctl start srvstats`
`systemctl enable srvstats`
srvstats will run on port `18080`
to add ssl you need to use a proxy

### Updating
navigate to srvstats directory
`systemctl stop srvstats`
`git pull`
`cd out`
`cmake --build .`
`systemctl start srvstats`

### License
MIT License

Copyright (c) 2024 Bartłomiej Postek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
