#pragma once

#include <string>

static std::string indexFile = R"html(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>srvstats</title>
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Roboto:wght@300&display=swap');
        *{
            font-family: "Roboto", sans-serif;
            font-weight: 300;
            font-style: normal;
        }
        body{
            background: #2c3e50;
            color: #bdc3c7;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            width: 100vw;
        }
        .box{
            display: flex;
            flex-direction: column;
            align-items: center;

            width: 100%;
            max-width: 48rem;
            border: 1px #34495e solid;
            border-radius: 1rem;
        }
        .data{
            width: calc(100% - 2rem);

            display: flex;
            flex-direction: row;
            justify-content: space-between;
        }
        .data-left{
            text-align: right;
            width: 92px;
        }
        .data-right{
            width: 42px;
        }
        .data-center{
            width: calc(48rem - 2rem - 92px - 42px - 2rem);
            display: block;
            width: max-content;
        }
        .data-center div{
            height: 20px;
            margin-top: 16px;
            margin-bottom: 16px;
            width: calc(48rem - 2rem - 92px - 42px - 2rem);
            max-width: calc(100vw - 2rem - 92px - 42px - 2rem);
            border-radius: 1rem;
            background: #95a5a6;
            overflow: hidden;
        }
        .data-center div div{
            height: 100%;
            transform: translateY(-16px);
            background: #3498db;
        }
        .data1{
            width: calc(100% - 2rem);

            display: flex;
            flex-direction: row;
            justify-content: space-between;
        }
        .data1-left{
            text-align: right;
            width: 80px;
        }
        .data1-right{
            width: calc(48rem - 2rem - 92px - 1rem);
            max-width: calc(100vw - 2rem - 92px - 1rem);
        }
    </style>
</head>
<body>
    <div class="box">
        <h1>srvstats <small>v0.1</small></h1>
        <div class="data1">
            <div class="data1-left">
                <p>Uptime:</p>
                <p>CPU Cores:</p>
            </div>
            <div class=" data1-right">
                <p><span class="_uptime">Loading...</span></p>
                <p><span class="_cores">Loading...</span></p>
            </div>
        </div>
        <div class="data">
            <div class="data-left">
                <p>CPU Ussage:</p>
                <p>Memory:</p>
                <p>Swap:</p>
            </div>
            <div class="data-center">
                <div><div class="_cpu_" style="width: 0%;"></div></div>
                <div><div class="_memory_" style="width: 0%;"></div></div>
                <div><div class="_swap_" style="width: 0%;"></div></div>
            </div>
            <div class="data-right">
                <p><span class="_cpu">0</span>%</p>
                <p><span class="_memory">0</span>%</p>
                <p><span class="_swap">0</span>%</p>
            </div>
        </div>
    </div>

    <script>
        const uptime = document.querySelector("._uptime")
        const cores = document.querySelector("._cores")
        const cpu = document.querySelector("._cpu")
        const memory = document.querySelector("._memory")
        const swap = document.querySelector("._swap")

        const _cpu = document.querySelector("._cpu_")
        const _memory = document.querySelector("._memory_")
        const _swap = document.querySelector("._swap_")

        const update = async () =>{
            var data = await fetch("/data")
            var d =  await data.json()

            uptime.innerHTML = d.uptime
            cores.innerHTML = d.cores
            cpu.innerHTML = d.cpu < 10 ? Math.round(d.cpu * 100) / 100 : Math.round(d.cpu)
            memory.innerHTML = d.memory < 10 ? Math.round(d.memory * 100) / 100 : Math.round(d.memory)
            swap.innerHTML = d.swap < 10 ? Math.round(d.swap * 100) / 100 : Math.round(d.swap)

            _cpu.style.width = d.cpu + "%"
            _memory.style.width = d.memory + "%"
            _swap.style.width = d.swap + "%"
        }
        update()
        setInterval(async () => {
            await update();
        }, 1000)
    </script>
</body>
</html>
)html";