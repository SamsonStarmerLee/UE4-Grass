# Unreal Engine 4 Stylized Grass

Stylized grass made in UE4.

[![Video of Grass](https://img.youtube.com/vi/_E243-z-QQ0/hqdefault.jpg)](https://youtu.be/_E243-z-QQ0)

Trees are from Lui's [Trees Library](https://forums.unrealengine.com/community/community-content-tools-and-tutorials/82804-free-trees-library).

<details>
<summary>Expand to see the entire graph</summary>
  
![Graph](Images/TotalGraph.png)
</details>

## Breakdown

### Color
<details>
<summary>Expand to see</summary>
  
![1](Images/1.png)

Here a worldspace noise texture is combined with vertex colours to fade grass colour between the root and tip. There is no diffuse texture.

![2](Images/2.png)

At distance, we colourize the grass towards a tint colour. This is driven by curve (LUT) to make the effect non-linear.
</details>

---

### Emissive
<details>
<summary>Expand to see</summary>
  
![3](Images/3.png)

This takes the untinted grass colour and reduces it before piping directly into emissive. This helps ensure some amount of grass colour is visible even at distance or in shadow.
</details>

---

### Camera Tilt
<details>
<summary>Expand to see</summary>
  
![4](Images/4.png)

Tilts the grass away from the camera at harsher angles. Intended to hide the gaps between blades when looking straight down.
Pivot point is an estimated position and comes from the Grass Interaction step.

This is based on [this GDC talk](https://youtu.be/wavnKZNSYqU?t=1156) about the foliage of Horizon: Zero Dawn.
</details>

---

### Height Variation
<details>
<summary>Expand to see</summary>
  
![5](Images/5.png)

This step applies a non-animated variation to height. This same effect can be created using the UE4 placement tool, so to really justify this step, some amount of animation or something should probably be added.

As-is, voronoi noise creates congruent ridges and peaks, implying the grass is doing really well in some places. True 'ridge noise' might be a good fit here.
</details>

---

### Grass Interaction
<details>
<summary>Expand to see</summary>
  
![6](Images/6.png)

To affect grass, actors can release particles with a vector field texture. As long as these particles draw to custom depth, they will be captured by a downward-facing orthographic camera. This is written to a render texture which the grass samples from. Directionality can the be found by un-projecting the vector field, which is then used to rotate the grass about its axis.

This approach has some benefits. For example, particles could be spawned for explosions to create shockwaves or other wind effects. Currently there is just one pre-made vector field texture, which only matches to circular objects. To handle more complex shapes, these fields could be generated on the fly. Potentially a simpler approach is just to use a depth buffer comparison, like you see with snow footprint simulations. This would lose the outward splay of grass blades, though.

This is based on the grass interaction described by Tommy Tran, found [here.](https://www.raywenderlich.com/6314-creating-interactive-grass-in-unreal-engine-4)
</details>

---

### Wind
<details>
<summary>Expand to see</summary>
  
![7](Images/7.png)

We also apply two levels of wind. One at scene-scale and another for smaller perturbations to imitate  localized gusts of wind. Both use vertex colours to avoid shifting the root of the grass around.
</details>

---

### Normal Movement

<details>
<summary>Expand to see</summary>
  
![8](Images/8.png)

![9](Images/9.png)

This technique comes from the "Boy and His Kite" demo.
We use two scrolling normal maps to create a wind-like effect that shifts the grass normals around (at rest, these normals point straight up).
As the normals animate, dark regions appear, which can look like wind, or cloud shadows.
</details>

---

## Other

Included is a basic C++ movement system. 

There is also an auto-adjusting camera system. Heavily adapted from [Daedelic Entertainment's camera system](https://github.com/DaedalicEntertainment/third-person-camera) created to adhere to this [GDC talk](https://youtu.be/C7307qRmlMI), "50 Game Camera Mistakes".
