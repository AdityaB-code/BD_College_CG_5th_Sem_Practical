% Load an image
original = imread('Balcony-ja.png');  % Use any image you like
imshow(original);
title('Original Image');

% Create a mask (simulate missing parts)
mask = false(size(original,1), size(original,2));
mask(100:150, 100:200) = true;  % simulate a damaged block
mask(200:250, 300:350) = true;

% Corrupt the image by setting masked regions to white
damaged = original;
damaged(repmat(mask, [1 1 3])) = 255;

figure;
imshow(damaged);
title('Damaged Image');

% Inpaint using regionfill
% Convert to grayscale for processing
gray = rgb2gray(damaged);
inpainted_gray = regionfill(gray, mask);

% Replace grayscale back into RGB for visual completion
inpainted_rgb = damaged;
for i = 1:3
    channel = damaged(:,:,i);
    channel(mask) = inpainted_gray(mask);
    inpainted_rgb(:,:,i) = channel;
end

figure;
imshow(uint8(inpainted_rgb));
title('Inpainted (Completed) Image');
