// https://openprocessing.org/sketch/2699492

// 頂点シェーダーのソースを定義しとるんよ
const vertShader = `#ifdef GL_ES
precision highp float;
#endif
attribute vec3 aPosition;
attribute vec2 aTexCoord;
varying vec2 vTexCoord;
void main() {
  vTexCoord = aTexCoord;                             // テクスチャ座標パススルー
  vec4 positionVec4 = vec4(aPosition, 1.0);          // 頂点位置をvec4に変換
  positionVec4.xy = positionVec4.xy * 2.0 - 1.0;     // NDC空間に正規化
  gl_Position = positionVec4;                        // 画面に頂点描画
}`; // 頂点シェーダー終わり

// フラグメントシェーダーのソースを定義しとるんよ
const fragShader = `#ifdef GL_ES
precision highp float;
#endif
uniform vec2 iResolution;
uniform float iTime;
varying vec2 vTexCoord;

// カラーパレット関数（Iñigo Quilezのヤツ）
vec3 palette( float t ){
    vec3 a = vec3(0.5, 0.5, 0.5);
    vec3 b = vec3(0.5, 0.5, 0.5);
    vec3 c = vec3(1.0, 1.0, 1.0);
    vec3 d = vec3(0.263,0.416,0.557);
    return sin(a) + cos(b)*cos( 6.28318*(c*cos(t)+sin(d)) );
}

// 距離関数（Rhombus, Hexagram, Circle）
float ndot(vec2 a, vec2 b ){ return a.x*b.x - a.y*b.y; }
float sdRhombus( in vec2 p, in vec2 b ){
  p = abs(p);
  float h = clamp( ndot(b-2.0*p,b)/dot(b,b), -1.0, 1.0 );
  float d = length( p-0.5*b*vec2(1.0-h,1.0+h) );
  return d * sign( p.x*b.y + p.y*b.x - b.x*b.y );
}
float sdHexagram( in vec2 p, in float r ){
  const vec4 k = vec4(-0.5,0.8660254,0.5773503,1.7320508);
  p = abs(p);
  p -= 2.0*min(dot(k.xy,p),0.0)*k.xy;
  p -= 2.0*min(dot(k.yx,p),0.0)*k.yx;
  p -= vec2(clamp(p.x,r*k.z,r*k.w),r);
  return length(p)*sign(p.y);
}
float sdCircle( vec2 p, float r ){ return length(p) - r; }

void main() {
  vec2 uv = vTexCoord * 2.0 - 1.0;                     // [-1,1]に変換
  const float scale = 1.0;                            // スケール因子
  uv.x *= scale * iResolution.x / iResolution.y;      // アスペクト比補正
  uv.y *= scale;                                      // 縦スケール
  vec2 uv0 = uv;                                      // 元UV保持
  vec3 finalColor = vec3(0.0);                        // 出力色初期化

  for (float i = 0.0; i < 4.0; i++) {                  // 多重ループで模様生成
    uv = fract(uv * 1.5) - 0.5;                       // フラクタル変形
    float d = length(uv) * exp(-length(uv0));         // 距離関数
    vec3 col = palette(length(uv0) + i*0.4 + iTime*0.4); // 色決定
    d = sin(d*8.0 + iTime) / 8.0;                     // 波紋効果
    d = abs(d) / 0.4;                                 // 調整
    d = pow(0.01 / tan(d), 1.2);                      // 輝度強調
    finalColor += col * d;                           // 合成
  }

  gl_FragColor = vec4(finalColor, 1.0);               // 最終色出力
}`; // フラグメントシェーダー終わり

let theShader; // p5.js用シェーダーオブジェクト格納変数

function setup() {
    createCanvas(windowWidth, windowHeight, WEBGL);     // キャンバス作成（WEBGLモード）
    pixelDensity(1);                                    // retina対策で解像度固定
    noStroke();                                         // 線無し
    theShader = createShader(vertShader, fragShader);   // シェーダー生成
}

function draw() {
    shader(theShader);                                  // シェーダー適用
    theShader.setUniform("iResolution", [width, height]); // 解像度渡しとる
    theShader.setUniform("iTime", millis() / 1000.0);     // 経過秒数渡しとる
    rect(-width/2, -height/2, width, height);            // 全面にシェーダー描画
}

function windowResized() {
    resizeCanvas(windowWidth, windowHeight);             // リサイズ時に再調整
}
