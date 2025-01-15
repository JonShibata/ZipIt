char char_html[]= "\
<HTML>\
\
<HEAD>\
    <title>ZipIt</title>\
    <style>\
        body {\
            background-color: #FFFFFF;\
            color: black;\
            font-size: 100px;\
        }\
\
        .rect {\
            width: 100%;\
            height: 100%;\
            border: none;\
            color: white;\
            padding: 0px 0px;\
            text-align: center;\
            text-decoration: none;\
            display: inline-block;\
            font-size: 30px;\
            margin: 0px 0px;\
            cursor: pointer;\
            font-family: monospace;\
        }\
\
        .WhiteBG {\
            background-color: #000000;\
        }\
\
        .BlueBG {\
            background-color: #0000AA;\
        }\
\
        .GreenBG {\
            background-color: #00AA00;\
        }\
\
        .GreyBG {\
            background-color: #888888;\
        }\
\
        .GreyBG15 {\
            background-color: #888888;\
            height: 15%;\
        }\
\
        .RedBG {\
            background-color: #AA0000;\
        }\
\
        .YellowBG {\
            background-color: #CCCC00;\
        }\
\
        .Title {\
            text-align: left;\
        }\
\
        .Units {\
            text-align: right;\
        }\
\
        .Debug {\
            color: #444;\
        }\
    </style>\
</head>\
\
<table width=100%>\
    <col width=28%>\
    <col width=22%>\
    <col width=18%>\
    <col width=32%>\
    <tr>\
        <td> <text class='rect WhiteBG Title'>Measured Temp</text> </td>\
        <td> <text id='T_Meas' class='rect WhiteBG Units'>xxx.x F &nbsp;</text> </td>\
        <td> <text id='b_Enable' class='rect GreenBG'>START</text> </td>\
        <td> <text id='b_Output' class='rect RedBG'>Burner On</text> </td>\
    </tr>\
</table>\
<font size=1px><br></font>\
<table width=100%>\
    <col width=28%>\
    <col width=22%>\
    <col width=18%>\
    <col width=16%>\
    <col width=16%>\
    <tr>\
        <td><text class='rect WhiteBG Title'>Target Temp</text> </td>\
        <td><input type='number' id='T_Target' class='rect WhiteBG Units'></input> </td>\
        <td></td>\
        <td><text id='T_TargetAdd' class='rect RedBG'> + </text> </td>\
        <td><text id='T_TargetSub' class='rect BlueBG'> - </text> </td>\
    </tr>\
    <tr>\
        <td><text class='rect WhiteBG Title'>Hysteresis</text> </td>\
        <td><input type='number' id='T_Hyst' class='rect WhiteBG Units'></input> </td>\
        <td></td>\
        <td><text id='T_HystAdd' class='rect RedBG'> + </text> </td>\
        <td><text id='T_HystSub' class='rect BlueBG'> - </text> </td>\
    </tr>\
</table>\
<font size=2px><br></font>\
<table width=100%>\
    <col width=28%>\
    <col width=22%>\
    <col width=18%>\
    <col width=16%>\
    <col width=16%>\
    <tr>\
        <td><text class='rect WhiteBG Title'>Manual Timer</text></td>\
        <td><text id='t_Manual' class='rect WhiteBG Units'>x.xx</text></td>\
        <td><text id='b_ManualRunning' class='rect GreyBG'>MODE</text></td>\
        <td><text id='Cnt_ManualAdd' class='rect RedBG'> + </text></td>\
        <td><text id='Cnt_ManualSub' class='rect BlueBG'> - </text></td>\
    </tr>\
    <tr>\
        <td><text class='rect WhiteBG Title'>Dip Timer</text> </td>\
        <td><text id='t_Dip' class='rect WhiteBG Units'>0:00</text> </td>\
        <td></td>\
        <td></td>\
        <td></td>\
    </tr>\
    <tr>\
        <td><text class='rect WhiteBG Title'>Recover Timer</text> </td>\
        <td><text id='t_Recover' class='rect WhiteBG Units'>0:00</text> </td>\
        <td></td>\
        <td></td>\
        <td></td>\
    </tr>\
</table>\
<font size=2px><br></font>\
<table width=100%>\
    <col width=28%>\
    <col width=22%>\
    <col width=18%>\
    <col width=16%>\
    <col width=16%>\
    <tr>\
        <td> <text class='rect WhiteBG Title'>Flame Off Cal</text> </td>\
        <td><input type='number' id='Cnt_FlameOff' class='rect WhiteBG Units'></input></td>\
        <td></td>\
        <td></td>\
        <td></td>\
\
    </tr>\
    <tr>\
        <td> <text class='rect WhiteBG Title'>Flame On Cal</text> </td>\
        <td><input type='number' id='Cnt_FlameOn' class='rect WhiteBG Units'></input></td>\
    </tr>\
    <tr>\
        <td><br><text class='rect WhiteBG Title'>Temperature 2</text></td>\
        <td><br><text id='T_Filt_2' class='rect WhiteBG Units'>xxx.x F &nbsp;</text></td>\
        <td></td>\
        <td></td>\
        <td></td>\
    </tr>\
    <tr>\
        <td> <text class='rect WhiteBG Title'>Temperature 3</text> </td>\
        <td> <text id='T_Filt_3' class='rect WhiteBG Units'>xxx.x F &nbsp;</text> </td>\
        <td></td>\
        <td></td>\
        <td></td>\
    </tr>\
</table><br><br>\
<font size=4% family='monospace'>\
    <p id='str_Debug1'></p>\
    <p id='str_Debug2'></p>\
</font>\
</body>\
<script>\
\
    document.getElementById('b_Enable').onclick = EnablePressed;\
\
    document.getElementById('b_ManualRunning').onclick = ManualPressed;\
    document.getElementById('Cnt_ManualAdd').onclick = ManualTimerAdd;\
    document.getElementById('Cnt_ManualSub').onclick = ManualTimerSub;\
\
    document.getElementById('T_Target').onchange = UpdateT_Target;\
    document.getElementById('T_TargetAdd').onclick = TargetAdd;\
    document.getElementById('T_TargetSub').onclick = TargetSub;\
\
    document.getElementById('T_Hyst').onchange = UpdateT_Hyst;\
    document.getElementById('T_HystAdd').onclick = HystAdd;\
    document.getElementById('T_HystSub').onclick = HystSub;\
\
    document.getElementById('Cnt_FlameOff').onchange = UpdateCnt_FlameOff;\
    document.getElementById('Cnt_FlameOn').onchange = UpdateCnt_FlameOn;\
\
\
\
\
\
    let b_InitComplete = sessionStorage.getItem('b_InitComplete');\
\
    if (b_InitComplete != 'true') {\
\
        sessionStorage.setItem('b_Enable', false);\
        sessionStorage.setItem('b_ManualRunning', false);\
\
        sessionStorage.setItem('Cnt_AboveLowerThresh', 0);\
        sessionStorage.setItem('Cnt_BelowLowerThresh', 0);\
        sessionStorage.setItem('Cnt_FlameOff', 0);\
        sessionStorage.setItem('Cnt_FlameOn', 180);\
        sessionStorage.setItem('Cnt_ManualMin', 10);\
        sessionStorage.setItem('Cnt_Loops', 0);\
        sessionStorage.setItem('Cnt_Output', 0);\
\
\
        sessionStorage.setItem('T_Meas', 0);\
        sessionStorage.setItem('T_Target', 350);\
        sessionStorage.setItem('T_Hyst', 3);\
\
        sessionStorage.setItem('t_StartDip', 0);\
        sessionStorage.setItem('t_StartRecover', 0);\
\
        sessionStorage.setItem('b_InitComplete', true);\
    }\
\
\
    main_loop();\
    UpdateGUI_Enable();\
    document.getElementById('Cnt_FlameOff').value = sessionStorage.getItem('Cnt_FlameOff');\
    document.getElementById('Cnt_FlameOn').value = sessionStorage.getItem('Cnt_FlameOn');\
    document.getElementById('T_Hyst').value = sessionStorage.getItem('T_Hyst');\
    document.getElementById('T_Target').value = sessionStorage.getItem('T_Target');\
\
\
    setInterval(main_loop, 500);\
\
\
    function main_loop() {\
\
        UpdateManualTimer();\
        ManualTimerStartStop();\
        UpdateAutoTimers();\
\
        let Cnt_Loops = sessionStorage.getItem('Cnt_Loops') * 1 + 1;\
\
        if (Cnt_Loops > 1) {\
\
            Cnt_Loops = 0;\
\
            let str_url = 'update' +\
                '?b_Enable=' + sessionStorage.getItem('b_Enable') +\
                '&Cnt_FlameOff=' + sessionStorage.getItem('Cnt_FlameOff') +\
                '&Cnt_FlameOn=' + sessionStorage.getItem('Cnt_FlameOn') +\
                '&T_Hyst=' + sessionStorage.getItem('T_Hyst') +\
                '&T_Target=' + sessionStorage.getItem('T_Target');\
\
            var xhttp = new XMLHttpRequest();\
\
            xhttp.onreadystatechange = function () {\
                if (this.readyState == 4 && this.status == 200) {\
\
                    let resp_json = JSON.parse(this.responseText);\
\
                    document.getElementById('T_Meas').innerHTML = parseFloat(resp_json.T_Meas).toFixed(1);\
                    sessionStorage.setItem('T_Meas', resp_json.T_Meas);\
\
                    document.getElementById('T_Filt_2').innerHTML = parseFloat(resp_json.T_Filt_2).toFixed(1);\
                    sessionStorage.setItem('T_Filt_2', resp_json.T_Filt_2);\
\
                    document.getElementById('T_Filt_3').innerHTML = parseFloat(resp_json.T_Filt_3).toFixed(1);\
                    sessionStorage.setItem('T_Filt_3', resp_json.T_Filt_3);\
\
                    sessionStorage.setItem('Cnt_Output', resp_json.Cnt_Output);\
                    /* Debug ****************************************************************** */\
                    document.getElementById('str_Debug2').innerHTML = resp_json.Cnt_Output;\
                    UpdateGUI_Output();\
                }\
            };\
            xhttp.open('GET', str_url, true);\
            xhttp.send();\
        }\
        sessionStorage.setItem('Cnt_Loops', Cnt_Loops);\
    }\
\
\
    function EnablePressed() {\
        if (sessionStorage.getItem('b_Enable') == 'true') {\
            sessionStorage.setItem('b_Enable', false);\
        } else {\
            sessionStorage.setItem('b_Enable', true);\
        }\
        UpdateGUI_Enable();\
    }\
\
\
    function UpdateGUI_Enable() {\
        if (sessionStorage.getItem('b_Enable') == 'true') {\
            document.getElementById('b_Enable').innerHTML = 'STOP';\
            document.getElementById('b_Enable').className = 'rect GreyBG';\
        } else {\
            document.getElementById('b_Enable').innerHTML = 'START';\
            document.getElementById('b_Enable').className = 'rect GreenBG';\
        }\
    }\
\
\
    function UpdateGUI_Output() {\
        let Cnt_FlameOutput = sessionStorage.getItem('Cnt_Output') * 1;\
        let Cnt_FlameOff = sessionStorage.getItem('Cnt_FlameOff') * 1;\
\
        if (Cnt_FlameOutput > Cnt_FlameOff) {\
            document.getElementById('b_Output').innerHTML = 'Burner On';\
            document.getElementById('b_Output').className = 'rect RedBG';\
        } else {\
            document.getElementById('b_Output').innerHTML = 'Burner Off';\
            document.getElementById('b_Output').className = 'rect GreyBG';\
        }\
    }\
\
\
    function UpdateManualTimer() {\
\
        let t_Delta = sessionStorage.getItem('Cnt_ManualMin') * 60 * 1000;\
\
        if (sessionStorage.getItem('b_ManualRunning') == 'true') {\
\
            let t_Now = new Date().getTime();\
            let t_ManualEnd = sessionStorage.getItem('t_ManualEnd');\
\
            t_Delta = t_ManualEnd - t_Now;\
        }\
\
        WriteTimer(t_Delta, 't_Manual');\
    }\
\
\
    function UpdateAutoTimers() {\
\
        let Cnt_AboveLowerThresh = sessionStorage.getItem('Cnt_AboveLowerThresh') * 1;\
        let Cnt_BelowLowerThresh = sessionStorage.getItem('Cnt_BelowLowerThresh') * 1;\
\
        let t_Now = new Date().getTime();\
        let t_StartDip = sessionStorage.getItem('t_StartDip') * 1;\
        let t_StartRecover = sessionStorage.getItem('t_StartRecover') * 1;\
\
        let T_Hyst = sessionStorage.getItem('T_Hyst') * 1;\
        let T_Meas = sessionStorage.getItem('T_Meas') * 1;\
        let T_Target = sessionStorage.getItem('T_Target') * 1;\
\
        if (T_Meas > (T_Target - T_Hyst)) {\
            Cnt_AboveLowerThresh++;\
            if (Cnt_AboveLowerThresh > 3) {\
                if (Cnt_BelowLowerThresh > 60) {\
                    t_StartRecover = t_Now;\
                }\
                Cnt_BelowLowerThresh = 0;\
            }\
        } else {\
            Cnt_BelowLowerThresh++;\
            if (Cnt_BelowLowerThresh > 3) {\
                if (Cnt_AboveLowerThresh > 60) {\
                    t_StartDip = t_Now;\
                }\
                Cnt_AboveLowerThresh = 0;\
            }\
        }\
\
        WriteTimer(t_Now - t_StartDip, 't_Dip');\
        WriteTimer(t_Now - t_StartRecover, 't_Recover');\
\
        /* Debug ****************************************************************** */\
        document.getElementById('str_Debug1').innerHTML =\
            Cnt_AboveLowerThresh + ' &nbsp; ' + Cnt_BelowLowerThresh;\
\
        sessionStorage.setItem('t_StartDip', t_StartDip);\
        sessionStorage.setItem('t_StartRecover', t_StartRecover);\
\
        sessionStorage.setItem('Cnt_AboveLowerThresh', Cnt_AboveLowerThresh);\
        sessionStorage.setItem('Cnt_BelowLowerThresh', Cnt_BelowLowerThresh);\
    }\
\
    function beep() {\
        var snd = new Audio('data:audio/wav;base64,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qJrx4KOQjahZxWbcZgztj2c49nKmkId44S71j0c8eV9yDK6uPRzx5X18eDvjvQ6yKo9ZSS6l//8elePK/Lf//IInrOF/FvDoADYAGBMGb7FtErm5MXMlmPAJQVgWta7Zx2go+8xJ0UiCb8LHHdftWyLJE0QIAIsI+UbXu67dZMjmgDGCGl1H+vpF4NSDckSIkk7Vd+sxEhBQMRU8j/12UIRhzSaUdQ+rQU5kGeFxm+hb1oh6pWWmv3uvmReDl0UnvtapVaIzo1jZbf/pD6ElLqSX+rUmOQNpJFa/r+sa4e/pBlAABoAAAAA3CUgShLdGIxsY7AUABPRrgCABdDuQ5GC7DqPQCgbbJUAoRSUj+NIEig0YfyWUho1VBBBA//uQZB4ABZx5zfMakeAAAAmwAAAAF5F3P0w9GtAAACfAAAAAwLhMDmAYWMgVEG1U0FIGCBgXBXAtfMH10000EEEEEECUBYln03TTTdNBDZopopYvrTTdNa325mImNg3TTPV9q3pmY0xoO6bv3r00y+IDGid/9aaaZTGMuj9mpu9Mpio1dXrr5HERTZSmqU36A3CumzN/9Robv/Xx4v9ijkSRSNLQhAWumap82WRSBUqXStV/YcS+XVLnSS+WLDroqArFkMEsAS+eWmrUzrO0oEmE40RlMZ5+ODIkAyKAGUwZ3mVKmcamcJnMW26MRPgUw6j+LkhyHGVGYjSUUKNpuJUQoOIAyDvEyG8S5yfK6dhZc0Tx1KI/gviKL6qvvFs1+bWtaz58uUNnryq6kt5RzOCkPWlVqVX2a/EEBUdU1KrXLf40GoiiFXK///qpoiDXrOgqDR38JB0bw7SoL+ZB9o1RCkQjQ2CBYZKd/+VJxZRRZlqSkKiws0WFxUyCwsKiMy7hUVFhIaCrNQsKkTIsLivwKKigsj8XYlwt/WKi2N4d//uQRCSAAjURNIHpMZBGYiaQPSYyAAABLAAAAAAAACWAAAAApUF/Mg+0aohSIRobBAsMlO//Kk4soosy1JSFRYWaLC4qZBYWFRGZdwqKiwkNBVmoWFSJkWFxX4FFRQWR+LsS4W/rFRb/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////VEFHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAU291bmRib3kuZGUAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAMjAwNGh0dHA6Ly93d3cuc291bmRib3kuZGUAAAAAAAAAACU=');  \
        snd.play();\
        }\
\
\
\
    function WriteTimer(t_Delta, str_element) {\
\
        let Cnt_Min = Math.floor((t_Delta % (1000 * 60 * 60)) / (1000 * 60));\
        let Cnt_Sec = Math.abs(Math.floor((t_Delta % (1000 * 60)) / 1000));\
\
        if (Cnt_Min > 0) {\
            document.getElementById(str_element).className = 'rect WhiteBG Units';\
        } else if (Cnt_Min > -1) {\
            document.getElementById(str_element).className = 'rect YellowBG Units';\
        } else {\
\
            Cnt_Min++; /* Account for negative delta calc */\
\
            if (Cnt_Sec == 60) {\
                Cnt_Sec = 0;\
                Cnt_Min--;\
            }\
\
            if (Cnt_Min == 0) {\
                Cnt_Min = '-0';\
            }\
\
            document.getElementById(str_element).className = 'rect RedBG Units';\
            beep();\
        }\
\
        if (Cnt_Sec < 10) {\
            Cnt_Sec = '0' + Cnt_Sec.toString();\
        }\
\
        document.getElementById(str_element).innerHTML =\
            Cnt_Min.toString() + ':' + Cnt_Sec.toString() + ' &nbsp';\
    }\
\
\
    function ManualPressed() {\
        if (sessionStorage.getItem('b_ManualRunning') == 'true') {\
            sessionStorage.setItem('b_ManualRunning', false);\
        } else {\
            sessionStorage.setItem('b_ManualRunning', true);\
\
            let Cnt_ManualMin = sessionStorage.getItem('Cnt_ManualMin') * 60 * 1000;\
            let now_plus_timer = new Date().getTime() + Cnt_ManualMin;\
\
            sessionStorage.setItem('t_ManualEnd', now_plus_timer);\
        }\
        ManualTimerStartStop();\
    }\
\
\
    function ManualTimerStartStop() {\
        if (sessionStorage.getItem('b_ManualRunning') == 'true') {\
            document.getElementById('b_ManualRunning').innerHTML = '<p>STOP<br>TIMER<p>';\
            document.getElementById('b_ManualRunning').className = 'rect GreyBG';\
        } else {\
            document.getElementById('b_ManualRunning').innerHTML = '<p>START<br>TIMER<p>';\
            document.getElementById('b_ManualRunning').className = 'rect GreenBG';\
\
        }\
    }\
\
\
    function ManualTimerAdd() {\
        if (sessionStorage.getItem('b_ManualRunning') == 'true') {\
            let t_ManualEnd = sessionStorage.getItem('t_ManualEnd') * 1 + 60 * 1000;\
            sessionStorage.setItem('t_ManualEnd', t_ManualEnd);\
        } else {\
            let Cnt_ManualMin = sessionStorage.getItem('Cnt_ManualMin') * 1 + 1;\
            sessionStorage.setItem('Cnt_ManualMin', Cnt_ManualMin);\
        }\
    }\
\
\
    function ManualTimerSub() {\
        if (sessionStorage.getItem('b_ManualRunning') == 'true') {\
            let t_ManualEnd = sessionStorage.getItem('t_ManualEnd') - 60 * 1000;\
            sessionStorage.setItem('t_ManualEnd', t_ManualEnd);\
        } else {\
            let Cnt_ManualMin = sessionStorage.getItem('Cnt_ManualMin') - 1;\
            sessionStorage.setItem('Cnt_ManualMin', Cnt_ManualMin);\
        }\
    }\
\
\
    function UpdateT_Target() {\
        let T_Target = document.getElementById('T_Target').value;\
        sessionStorage.setItem('T_Target', T_Target);\
    }\
\
    function TargetAdd() {\
        let T_Target = sessionStorage.getItem('T_Target') * 1 + 5;\
        sessionStorage.setItem('T_Target', T_Target);\
        document.getElementById('T_Target').value = sessionStorage.getItem('T_Target');\
    }\
\
\
    function TargetSub() {\
        let T_Target = sessionStorage.getItem('T_Target') - 5;\
        sessionStorage.setItem('T_Target', T_Target);\
        document.getElementById('T_Target').value = sessionStorage.getItem('T_Target');\
    }\
\
\
    function UpdateT_Hyst() {\
        let T_Hyst = document.getElementById('T_Hyst').value;\
        sessionStorage.setItem('T_Hyst', T_Hyst);\
    }\
\
\
    function HystAdd() {\
        let T_Hyst = sessionStorage.getItem('T_Hyst') * 1 + 1;\
        sessionStorage.setItem('T_Hyst', T_Hyst);\
        document.getElementById('T_Hyst').value = sessionStorage.getItem('T_Hyst');\
    }\
\
\
    function HystSub() {\
        let T_Hyst = sessionStorage.getItem('T_Hyst') - 1;\
        sessionStorage.setItem('T_Hyst', T_Hyst);\
        document.getElementById('T_Hyst').value = sessionStorage.getItem('T_Hyst');\
    }\
\
\
    function UpdateCnt_FlameOff() {\
        sessionStorage.setItem('Cnt_FlameOff',\
            document.getElementById('Cnt_FlameOff').value);\
    }\
\
\
    function UpdateCnt_FlameOn() {\
        sessionStorage.setItem('Cnt_FlameOn',\
            document.getElementById('Cnt_FlameOn').value);\
    }\
</script>\
\
</html>";
