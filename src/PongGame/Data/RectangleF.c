#include "RectangleF.h"

int RectangleF_IsCollisionWith(RectangleF this, RectangleF other)
{
    return 
        other.LeftUpCornerPosition.X < this.LeftUpCornerPosition.X + this.Size.X &&
        this.LeftUpCornerPosition.X < other.LeftUpCornerPosition.X + other.Size.X &&
        other.LeftUpCornerPosition.Y < this.LeftUpCornerPosition.Y + this.Size.Y &&
        this.LeftUpCornerPosition.Y < other.LeftUpCornerPosition.Y + other.Size.Y;
}