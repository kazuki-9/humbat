#include "flower.h"

void flower::drawFlower(QPainter *painter, int x, int y) {
    // Draw a flower
    painter->setBrush(Qt::red); // Set brush color to red for the petals
    painter->drawEllipse(x, y, 20, 20); // Draw the petals
    painter->setBrush(Qt::yellow); // Set brush color to yellow for the center
    painter->drawEllipse(x + 8, y + 8, 4, 4); // Draw the center of the flower
}
