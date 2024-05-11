//Taken from here https://habr.com/ru/articles/650021/

using System.Runtime.InteropServices;

namespace PongSharp.Tools;

internal class TimerWithNtDelayExecution
{
    [DllImport("ntdll.dll", SetLastError = true)]
    private static extern void NtSetTimerResolution(uint desiredResolution, bool setResolution, ref uint currentResolution);

    [DllImport("ntdll.dll")]
    private static extern void NtDelayExecution(bool alertable, ref long delayInterval);

    private Thread _thread;
    private bool _running;

    public void Start(int intervalMs, Action callback)
    {
        var res = (uint)(intervalMs * 10000);
        NtSetTimerResolution(res, true, ref res);

        _thread = new Thread(() =>
        {
            _running = true;

            while (_running)
            {
                var interval = -intervalMs * 10000L;
                callback();
                NtDelayExecution(false, ref interval);
            }
        }) { Priority = ThreadPriority.Highest };

        _thread.Start();
    }

    public void Stop() => _running = false;
}