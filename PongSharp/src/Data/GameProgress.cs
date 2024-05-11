namespace PongSharp.Data;

internal class GameProgress
{
    public int LeftPlayerScore { get; private set; }
    public int RightPlayerScore { get; private set; }
    
    public void IncreaseLeftPlayerScore() => LeftPlayerScore++;

    public void IncreaseRightPlayerScore() => RightPlayerScore++;
}