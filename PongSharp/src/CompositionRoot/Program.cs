namespace PongSharp.CompositionRoot;

internal class Program
{
    private static void Main()
    {
        var game = new Game();
        
        game.Start();

        Thread.CurrentThread.Join();
    }
}