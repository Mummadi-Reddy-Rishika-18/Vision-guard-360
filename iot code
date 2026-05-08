import processing.serial.*;
// =====================================================
// VISION GUARD 360
// AI BLIND-SPOT SAFETY SYSTEM
// =====================================================
// =====================================================
// SERIAL
// =====================================================
Serial myPort;
String data = "";
// =====================================================
// SENSOR VALUES
// =====================================================
float front = 20;
float back  = 20;
float left  = 20;
float right = 20;
// =====================================================
// RADAR SETTINGS
// =====================================================
float MAX_RANGE = 20;
float DANGER_DIST  = 6;
float WARNING_DIST = 14;
// =====================================================
// IMAGE + FONT
// =====================================================
PImage excavator;
PFont monoFont;
// =====================================================
// RADAR SWEEP
// =====================================================
float sweepAngle = 0;
// =====================================================
// SETUP
// =====================================================
void setup()
{
  // PERFECT FIT FOR 1920x1080
  size(1500, 820);
  smooth();
  frameRate(60);
  excavator = loadImage("excavator.png");
  monoFont = createFont("Courier New", 16, true);
  textFont(monoFont);
  println(Serial.list());
  // CHANGE PORT NUMBER IF NEEDED
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');
}
// =====================================================
// DRAW
// =====================================================
void draw()
{
  background(2, 8, 10);
  drawDangerFlash();
  pushMatrix();
  // MOVED SLIGHTLY UP
  translate(width/2, height/2 - 40);
  drawGrid();
  drawRadarRings();
  drawRadarSweep();
  drawZoneArc(front, -HALF_PI);
  drawZoneArc(back, HALF_PI);
  drawZoneArc(left, PI);
  drawZoneArc(right, 0);
  drawExcavator();
  // ===================================================
  // TARGETS
  // ===================================================
  drawTarget(front, "FRONT");
  drawTarget(back, "BACK");
  drawTarget(left, "LEFT");
  drawTarget(right, "RIGHT");
  drawTitle();
  popMatrix();
  drawStatusPanel();
}
// =====================================================
// GRID
// =====================================================
void drawGrid()
{
  stroke(0, 255, 120, 10);
  strokeWeight(1);
  int spacing = 45;
  for(int x = -900; x <= 900; x += spacing)
  {
    line(x, -900, x, 900);
  }
  for(int y = -900; y <= 900; y += spacing)
  {
    line(-900, y, 900, y);
  }
}
// =====================================================
// RADAR RINGS
// =====================================================
void drawRadarRings()
{
  noFill();
  strokeWeight(1);
  // PERFECT FIT
  int[] radii = {80, 160, 240, 320, 400};
  for(int i = 0; i < radii.length; i++)
  {
    stroke(0, 255, 120, 30);
    ellipse(0, 0, radii[i]*2, radii[i]*2);
    fill(0, 255, 120, 100);
    textSize(14);
    text(i*5 + " cm",
         radii[i] + 10,
         0);
    noFill();
  }
  stroke(0, 255, 120, 18);
  line(-400, 0, 400, 0);
  line(0, -400, 0, 400);
}
// =====================================================
// RADAR SWEEP
// =====================================================
void drawRadarSweep()
{
  pushMatrix();
  rotate(radians(sweepAngle));
  noStroke();
  fill(0, 255, 120, 20);
  arc(0,
      0,
      800,
      800,
      radians(-10),
      radians(10));
  popMatrix();
  sweepAngle += 2.5;
  if(sweepAngle >= 360)
  {
    sweepAngle = 0;
  }
}
// =====================================================
// ZONE ARC
// =====================================================
void drawZoneArc(float dist, float angle)
{
  float arcSpan = radians(80);
  float r1 = 80;
  float r2 = 400;
  noStroke();
  fill(getZoneColor(dist, 40));
  beginShape();
  for(float a = angle - arcSpan/2;
      a <= angle + arcSpan/2;
      a += 0.03)
  {
    vertex(r1*cos(a),
           r1*sin(a));
  }
  for(float a = angle + arcSpan/2;
      a >= angle - arcSpan/2;
      a -= 0.03)
  {
    vertex(r2*cos(a),
           r2*sin(a));
  }
  endShape(CLOSE);
}
// =====================================================
// COLOR
// =====================================================
color getZoneColor(float dist, int alpha)
{
  if(dist <= DANGER_DIST)
  {
    return color(255, 40, 40, alpha);
  }
  if(dist <= WARNING_DIST)
  {
    return color(255, 180, 0, alpha);
  }
  return color(0, 255, 120, 25);
}
// =====================================================
// EXCAVATOR
// =====================================================
void drawExcavator()
{
  imageMode(CENTER);
  if(excavator != null)
  {
    noStroke();
    fill(0, 255, 120, 18);
    ellipse(0, 0, 130, 130);
    image(excavator, 0, 0, 140, 280);
  }
}
// =====================================================
// RADAR TARGET
// =====================================================
void drawTarget(float dist, String side)
{
  if(dist > MAX_RANGE)
  {
    return;
  }
  // PERFECT POSITIONING
  float radarDist =
    map(dist,
        0,
        20,
        50,
        400);
  radarDist =
    constrain(radarDist,
              50,
              400);
  float x = 0;
  float y = 0;
  if(side.equals("FRONT"))
  {
    y = -radarDist;
  }
  else if(side.equals("BACK"))
  {
    y = radarDist;
  }
  else if(side.equals("LEFT"))
  {
    x = -radarDist;
  }
  else if(side.equals("RIGHT"))
  {
    x = radarDist;
  }
  // ===================================================
  // TARGET COLOR
  // ===================================================
  color radarColor;
  if(dist <= DANGER_DIST)
  {
    radarColor = color(255, 40, 40);
  }
  else if(dist <= WARNING_DIST)
  {
    radarColor = color(255, 180, 0);
  }
  else
  {
    radarColor = color(0, 255, 120);
  }
  // ===================================================
  // RADAR LINE
  // ===================================================

  stroke(radarColor, 120);
  strokeWeight(2);
  line(0, 0, x, y);
  // ===================================================
  // TARGET BOX
  // ===================================================
  stroke(radarColor);
  noFill();
  rectMode(CENTER);
  rect(x, y, 30, 30);
  // ===================================================
  // TARGET DOT
  // ===================================================
  noStroke();
  fill(radarColor);
  ellipse(x, y, 16, 16);
  // ===================================================
  // BLINK
  // ===================================================
  float blink = sin(frameCount * 0.18);
  if(blink > 0)
  {
    fill(255);
    ellipse(x, y, 5, 5);
  }
  // ===================================================
  // PULSE
  // ===================================================
  noFill();
  stroke(radarColor, 180);
  strokeWeight(2);
  float pulse =
    map(sin(frameCount * 0.08),
        -1,
        1,
        22,
        55);
  ellipse(x, y, pulse, pulse);
  stroke(radarColor, 90);
  ellipse(x, y, pulse + 18, pulse + 18);
  // ===================================================
  // DISTANCE TEXT
  // ===================================================
  fill(255);
  textAlign(CENTER);
  textSize(14);
  text(int(dist) + " cm",
       x,
       y - 24);
  // ===================================================
  // SIDE LABEL
  // ===================================================
  fill(radarColor);
  textSize(11);
  text(side,
       x,
       y + 28);
}
// =====================================================
// TITLE + CLOCK + GPS
// =====================================================
void drawTitle()
{
  // MAIN TITLE
  fill(0,255,120);
  textAlign(CENTER);
  textSize(42);
  text("VISION GUARD 360",
       0,
       -370);
  // SUBTITLE
  fill(120);
  textSize(18);
  text("AI BLIND-SPOT SAFETY SYSTEM",
       0,
       -338);
  // LIVE TIME
  fill(0,255,120);
  textSize(20);
  String currentTime =
    nf(hour(),2) + ":" +
    nf(minute(),2) + ":" +
    nf(second(),2);
  text(currentTime,
       640,
       -370);
  // GPS STATUS
  fill(0,200,255);
  textSize(18);
  text("GPS LINKED",
       -640,
       -370);
}
// =====================================================
// DANGER FLASH
// =====================================================
void drawDangerFlash()
{
  boolean danger =
    front <= DANGER_DIST ||
    back  <= DANGER_DIST ||
    left  <= DANGER_DIST ||
    right <= DANGER_DIST;
  if(danger)
  {
    float blink = sin(frameCount * 0.25);
    int alpha =
      int(map(blink,
              -1,
              1,
              0,
              18));
    noStroke();
    fill(255, 0, 0, alpha);
    rect(0, 0, width, height);
  }
}
// =====================================================
// STATUS PANEL
// =====================================================
void drawStatusPanel()
{
  int px = 25;
  // MOVED UP
  int py = height - 150;
  noStroke();
  fill(0, 20, 10, 220);
  rect(px, py, 340, 150, 10);
  fill(0, 255, 120);
  textSize(20);
  textAlign(LEFT);
  text("SENSOR STATUS",
       px + 15,
       py + 25);
  drawStatusRow("FRONT",
                front,
                px + 15,
                py + 55);
  drawStatusRow("LEFT",
                left,
                px + 15,
                py + 85);
  drawStatusRow("RIGHT",
                right,
                px + 15,
                py + 115);
  drawStatusRow("BACK",
                back,
                px + 15,
                py + 145);
}
// =====================================================
// STATUS ROW
// =====================================================
void drawStatusRow(String label,
                   float dist,
                   float x,
                   float y)
{
  fill(170);
  textSize(16);
  text(label, x, y);
  float barX = x + 90;
  float barW = 130;
  noStroke();
  fill(40);
  rect(barX, y - 12, barW, 8, 3);
  float pct =
    constrain(map(dist,
                  0,
                  MAX_RANGE,
                  barW,
                  0),
              0,
              barW);
  fill(getZoneColor(dist, 255));
  rect(barX, y - 12, pct, 8, 3);
  fill(255);
  textAlign(RIGHT);
  if(dist <= MAX_RANGE)
  {
    text(int(dist) + " cm",
         barX + 190,
         y);
  }
  else
  {
    text("CLEAR",
         barX + 190,
         y);
  }
  textAlign(LEFT);
}
// =====================================================
// SERIAL EVENT
// =====================================================
void serialEvent(Serial myPort)
{
  data = myPort.readStringUntil('\n');
  if(data != null)
  {
    data = trim(data);
    println(data);
    // FORMAT:
    // front,back,left,right
    String[] values = split(data, ',');
    if(values.length == 4)
    {
      front = float(values[0]);
      back  = float(values[1]);
      left  = float(values[2]);
      right = float(values[3]);
    }
  }
}
