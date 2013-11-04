#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <teleop_msgs/CompressedPointCloud2.h>
#include <zlib.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/ros/conversions.h>
#include <pcl/compression/octree_pointcloud_compression.h>
#include <opportunistic_link/pc30_compression.h>

#ifndef POINTCLOUD_COMPRESSION_H
#define POINTCLOUD_COMPRESSION_H

namespace pointcloud_compression
{
    void dealocate_pcl_pointcloud_fn(pcl::PointCloud<pcl::PointXYZRGB>* p)
    {
    }

    void dealocate_sensor_messages_pointcloud2_fn(sensor_msgs::PointCloud2* p)
    {
    }

    class PointCloudHandler
    {
    protected:

        pcl::VoxelGrid<sensor_msgs::PointCloud2> voxel_filter_;
        pcl::octree::PointCloudCompression<pcl::PointXYZRGB> pcl_encoder_;
        pcl::octree::PointCloudCompression<pcl::PointXYZRGB> pcl_decoder_;
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr uncompressed_cloud_ptr_;
        pc30_compression::PC30Compressor pc30_encoder_;
        pc30_compression::PC30Compressor pc30_decoder_;

    public:

        PointCloudHandler()
        {
            uncompressed_cloud_ptr_ = pcl::PointCloud<pcl::PointXYZRGB>::Ptr(new pcl::PointCloud<pcl::PointXYZRGB>());
        }

        ~PointCloudHandler()
        {
        }

        void reset_encoder();

        void reset_decoder();

        std::vector<uint8_t> decompress_bytes(std::vector<uint8_t>& compressed);

        std::vector<uint8_t> compress_bytes(std::vector<uint8_t>& uncompressed);

        sensor_msgs::PointCloud2 decompress_pointcloud2(teleop_msgs::CompressedPointCloud2& compressed);

        teleop_msgs::CompressedPointCloud2 compress_pointcloud2(sensor_msgs::PointCloud2& cloud, uint8_t compression_type, float filter_size);

        teleop_msgs::CompressedPointCloud2 compress_pointcloud2(sensor_msgs::PointCloud2& cloud, uint8_t compression_type);

    };
}

#endif // POINTCLOUD_COMPRESSION_H
