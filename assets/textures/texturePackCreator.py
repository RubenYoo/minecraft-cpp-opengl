import os
from PIL import Image

WIDTH: int = 256
HEIGHT: int = 256

texture_pack = Image.new(mode="RGB", size=(WIDTH, HEIGHT))

texture_blocks = [file for file in os.listdir('./images/') if file.endswith('.png')]

if len(texture_blocks) > 256:
    print("Too much textures, the max is 256")
    exit()

texture_blocks.sort()

for texture_block in texture_blocks:
    block = Image.open('./images/' + texture_block)
    if block.width != 16 or block.height != 16:
        (block.resize((16, 16))).save('./images/' + texture_block)

for index, texture_block in enumerate(texture_blocks):
    texture_pack.paste(Image.open('./images/' + texture_block), (index * 16, (index * 16) // 256))

texture_pack.save('./texture_pack.png')


