

// compute distance between two 3D points

__kernel void distance(__global const float *x1,
					   __global const float *y1,
					   __global const float *z1,
					   __global const float *x2,
					   __global const float *y2,
					   __global const float *z2,
					   __global float *dist)
{
	int i = get_global_id(0);
	dist[i] = sqrt((x1[i] - x2[i]) * (x1[i] - x2[i]) +
				   (y1[i] - y2[i]) * (y1[i] - y2[i]) +
				   (z1[i] - z2[i]) * (z1[i] - z2[i]));
}
