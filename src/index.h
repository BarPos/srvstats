#pragma once

#include <string>

static std::string indexFile = R"html(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>srvstats</title>
</head>
<body>
    <h1>srvstats</h1>
    <p>Uptime: <span class="_uptime">Loading...</span></p>
    <p>CPU Cores: <span class="_cores">Loading...</span></p>
    <p>CPU Ussage: <span class="_cpu">0</span>%</p>
    <p>Memory: <span class="_memory">0</span>%</p>
    <p>Swap: <span class="_swap">0</span>%</p>

    <script>
        const uptime = document.querySelector("._uptime")
        const cores = document.querySelector("._cores")
        const cpu = document.querySelector("._cpu")
        const memory = document.querySelector("._memory")
        const swap = document.querySelector("._swap")

        const update = async () =>{
            var data = await fetch("/data")
            var d =  await data.json()

            uptime.innerHTML = d.uptime
            cores.innerHTML = d.cores
            cpu.innerHTML = Math.round(d.cpu * 100) / 100
            memory.innerHTML = Math.round(d.memory * 100) / 100
            swap.innerHTML = Math.round(d.swap * 100) / 100
        }
        update()
        setInterval(async () => {
            await update();
        }, 1000)
    </script>
</body>
</html>
)html";