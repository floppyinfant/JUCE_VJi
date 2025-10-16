To prepare ShaderToy shader code to run in your JUCE plugin, you need to convert ShaderToy's conventions to JUCE's `OpenGLGraphicsContextCustomShader` format. Let me show you how to do this:

## Key Differences Between ShaderToy and JUCE

### ShaderToy:
- Uses `mainImage(out vec4 fragColor, in vec2 fragCoord)` as entry point
- Provides uniforms like `iResolution`, `iTime`, `iMouse`, etc.
- `fragCoord` is in pixel coordinates (0 to resolution)

### JUCE:
- Uses `main()` as entry point
- Provides `pixelPos` (vec2), `pixelAlpha` (float/vec4)
- You need to provide your own uniforms

## Conversion Template

Here's how to convert a ShaderToy shader to JUCE format:

```c++
// ... existing code ...

private:
    // Add method to convert ShaderToy code
    juce::String convertShaderToyToJUCE(const juce::String& shaderToyCode);
    
    // Add method to create wrapper with uniforms
    juce::String wrapWithUniforms(const juce::String& shaderCode);

// ... existing code ...
```


```c++
// ... existing code ...

juce::String ShaderEditor::convertShaderToyToJUCE(const juce::String& shaderToyCode)
{
    juce::String juceShader;
    
    // Add JUCE-compatible uniforms header
    juceShader += "// Converted from ShaderToy\n\n";
    juceShader += "uniform vec3 iResolution;\n";
    juceShader += "uniform float iTime;\n";
    juceShader += "uniform vec4 iMouse;\n";
    juceShader += "uniform float iTimeDelta;\n";
    juceShader += "uniform int iFrame;\n\n";
    
    // Add the ShaderToy code (keep mainImage function)
    juceShader += shaderToyCode;
    juceShader += "\n\n";
    
    // Add JUCE main() wrapper
    juceShader += "void main()\n";
    juceShader += "{\n";
    juceShader += "    vec4 fragColor;\n";
    juceShader += "    mainImage(fragColor, pixelPos);\n";
    juceShader += "    gl_FragColor = pixelAlpha * fragColor;\n";
    juceShader += "}\n";
    
    return juceShader;
}

juce::String ShaderEditor::wrapWithUniforms(const juce::String& shaderCode)
{
    // Check if it's already a ShaderToy shader (has mainImage)
    if (shaderCode.contains("mainImage"))
    {
        return convertShaderToyToJUCE(shaderCode);
    }
    
    // Otherwise assume it's already JUCE-compatible
    return shaderCode;
}

// ... existing code ...
```


## Manual Conversion Example

Here's a complete example of converting a simple ShaderToy shader:

### Original ShaderToy Code:
```
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;
    
    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
    
    // Output to screen
    fragColor = vec4(col,1.0);
}
```


### Converted JUCE Code:
```
uniform vec3 iResolution;
uniform float iTime;

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;
    
    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
    
    // Output to screen
    fragColor = vec4(col,1.0);
}

void main()
{
    vec4 fragColor;
    mainImage(fragColor, pixelPos);
    gl_FragColor = pixelAlpha * fragColor;
}
```


## Setting Uniform Values in JUCE

You'll need to update the uniforms before rendering. Modify the `paint()` method:

```c++
void ShaderEditor::paint(juce::Graphics& g)
{
    g.fillCheckerBoard (getLocalBounds().toFloat(), 48.0f, 48.0f, juce::Colours::lightgrey, juce::Colours::white);

    if (shader.get() == nullptr || shader->getFragmentShaderCode() != fragmentCode)
    {
        shader.reset();

        if (fragmentCode.isNotEmpty())
        {
            shader.reset (new juce::OpenGLGraphicsContextCustomShader (fragmentCode));

            auto result = shader->checkCompilation (g.getInternalContext());

            if (result.failed())
            {
                statusLabel.setText (result.getErrorMessage(), juce::NotificationType::dontSendNotification);
                shader.reset();
            }
        }
    }

    if (shader.get() != nullptr)
    {
        statusLabel.setText ({}, juce::NotificationType::dontSendNotification);
        
        // Set ShaderToy-compatible uniforms
        auto& glContext = g.getInternalContext();
        
        if (auto* shaderProgram = shader->program.get())
        {
            shaderProgram->use();
            
            // iResolution
            if (auto* uniform = shaderProgram->getUniform("iResolution"))
                uniform->set((float)getWidth(), (float)getHeight(), 1.0f);
            
            // iTime (you'll need to track time)
            if (auto* uniform = shaderProgram->getUniform("iTime"))
                uniform->set((float)(juce::Time::getMillisecondCounterHiRes() * 0.001));
            
            // iMouse (you'll need to track mouse)
            if (auto* uniform = shaderProgram->getUniform("iMouse"))
                uniform->set(0.0f, 0.0f, 0.0f, 0.0f);
            
            // iFrame
            if (auto* uniform = shaderProgram->getUniform("iFrame"))
                uniform->set(frameCounter++);
        }

        shader->fillRect (g.getInternalContext(), getLocalBounds());
    }
}
```


## Add Time Tracking

```c++
// ... existing code ...

private:
    int frameCounter = 0;
    double startTime = 0.0;

// ... existing code ...
```


```c++
ShaderEditor::ShaderEditor(PluginAudioProcessor& p)
    : juce::AudioProcessorEditor(&p), processor(p)
{
    startTime = juce::Time::getMillisecondCounterHiRes() * 0.001;
    
    // ... existing code ...
}
```


## Add a ShaderToy Preset

```c++
juce::Array<ShaderEditor::ShaderPreset> ShaderEditor::getPresets()
{
    // ... existing presets ...

    ShaderPreset newPresets[] = 
    {
        // ... existing presets ...
        
        {
            "ShaderToy - Plasma",
            
            "uniform vec3 iResolution;\n"
            "uniform float iTime;\n"
            "\n"
            "void mainImage(out vec4 fragColor, in vec2 fragCoord)\n"
            "{\n"
            "    vec2 uv = fragCoord / iResolution.xy;\n"
            "    vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0,2,4));\n"
            "    fragColor = vec4(col, 1.0);\n"
            "}\n"
            "\n"
            "void main()\n"
            "{\n"
            "    vec4 fragColor;\n"
            "    mainImage(fragColor, pixelPos);\n"
            "    gl_FragColor = pixelAlpha * fragColor;\n"
            "}\n"
        }
    };
    
    return juce::Array<ShaderPreset>(newPresets, numElementsInArray(newPresets));
}
```


## Summary

To convert ShaderToy shaders to JUCE:

1. **Add uniform declarations** at the top (`iResolution`, `iTime`, etc.)
2. **Keep the `mainImage()` function** as-is
3. **Add a `main()` wrapper** that calls `mainImage()` with `pixelPos`
4. **Set uniform values** in the `paint()` method before rendering
5. **Use `pixelAlpha`** to apply JUCE's alpha blending

This approach lets you paste ShaderToy code with minimal modifications!