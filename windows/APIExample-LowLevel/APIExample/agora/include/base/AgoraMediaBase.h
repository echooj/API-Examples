//
//  Agora Engine SDK
//
//  Created by Sting Feng in 2017-11.
//  Copyright (c) 2017 Agora.io. All rights reserved.

#pragma once  // NOLINT(build/header_guard)
#include <stdint.h>
#include <limits>

namespace agora {

namespace rtc {
typedef unsigned int uid_t;
typedef unsigned int track_id_t;
typedef unsigned int conn_id_t;

static const unsigned int DEFAULT_CONNECTION_ID = 0;
static const unsigned int DUMMY_CONNECTION_ID = (std::numeric_limits<unsigned int>::max)();
}  // namespace rtc

namespace media {

static const uint8_t kMaxCodecNameLength = 50;

/** The packet information, i.e., infomation contained in RTP heaader.
*/
struct PacketOptions {
  // Rtp timestamp
  uint32_t time_stamp;
  PacketOptions()
      : time_stamp(0) {}
};


/** The video pixel format.
 */
enum VIDEO_PIXEL_FORMAT {
  /** 0: The video pixel format is unknown.
   */
  VIDEO_PIXEL_UNKNOWN = 0,
  /** 1: The video pixel format is I420.
   */
  VIDEO_PIXEL_I420 = 1,
  /** 2: The video pixel format is BGRA.
   */
  VIDEO_PIXEL_BGRA = 2,
  /** 3: The video pixel format is planar YUV 4:2:2.
   */
  VIDEO_PIXEL_I422 = 3,
  /** 2: The video pixel format is RGBA.
   */
  VIDEO_PIXEL_RGBA = 4,
  /** 8: The video pixel format is NV12.
   */
  VIDEO_PIXEL_NV12 = 8,
};

/** The external video frame.
 */
struct ExternalVideoFrame {
  /** The video buffer type.
   */
  enum VIDEO_BUFFER_TYPE {
    /** 1: The video buffer in the format of raw data.
     */
    VIDEO_BUFFER_RAW_DATA = 1,
  };

  /** The buffer type. See #VIDEO_BUFFER_TYPE
   */
  VIDEO_BUFFER_TYPE type;
  /** The pixel format. See #VIDEO_PIXEL_FORMAT
   */
  VIDEO_PIXEL_FORMAT format;
  /** The video buffer.
   */
  void* buffer;
  /** Line spacing of the incoming video frame, which must be in pixels instead of bytes. For
   * textures, it is the width of the texture.
   */
  int stride;
  /** Height of the incoming video frame.
   */
  int height;
  /** [Raw data related parameter] The number of pixels trimmed from the left. The default value is
   * 0.
   */
  int cropLeft;
  /** [Raw data related parameter] The number of pixels trimmed from the top. The default value is
   * 0.
   */
  int cropTop;
  /** [Raw data related parameter] The number of pixels trimmed from the right. The default value is
   * 0.
   */
  int cropRight;
  /** [Raw data related parameter] The number of pixels trimmed from the bottom. The default value
   * is 0.
   */
  int cropBottom;
  /** [Raw data related parameter] The clockwise rotation of the video frame. You can set the
   * rotation angle as 0, 90, 180, or 270. The default value is 0.
   */
  int rotation;
  /** Timestamp of the incoming video frame (ms). An incorrect timestamp results in frame loss or
   * unsynchronized audio and video.
   */
  long long timestamp;
};

/** Definition of VideoFrame.

The video data format is in YUV420. The buffer provides a pointer to a pointer. However, the
interface cannot modify the pointer of the buffer, but can only modify the content of the buffer.

*/
struct VideoFrame {
  VIDEO_PIXEL_FORMAT type;
  /** Video pixel width.
   */
  int width;  // width of video frame
  /** Video pixel height.
   */
  int height;  // height of video frame
  /** Line span of Y buffer in YUV data.
   */
  int yStride;  // stride of Y data buffer
  /** Line span of U buffer in YUV data.
   */
  int uStride;  // stride of U data buffer
  /** Line span of V buffer in YUV data.
   */
  int vStride;  // stride of V data buffer
  /** Pointer to the Y buffer pointer in the YUV data.
   */
  uint8_t* yBuffer;  // Y data buffer
  /** Pointer to the U buffer pointer in the YUV data.
   */
  uint8_t* uBuffer;  // U data buffer
  /** Pointer to the V buffer pointer in the YUV data
   */
  uint8_t* vBuffer;  // V data buffer
  /** Set the rotation of this frame before rendering the video, and it supports 0, 90, 180, 270
   * degrees clockwise.
   */
  int rotation;  // rotation of this frame (0, 90, 180, 270)
  /** Timestamp to render the video stream. It instructs the users to use this timestamp to
  synchronize the video stream render while rendering the video streams.

  Note: This timestamp is for rendering the video stream, not for capturing the video stream.
  */
  int64_t renderTimeMs;
  int avsync_type;
};

/**
 * @brief Player state
 *
 */
enum MEDIA_PLAYER_STATE {
  /** Player idle
   */
  PLAYER_STATE_IDLE = 0,
  /** Opening media file
   */
  PLAYER_STATE_OPENING,
  /** Media file opened successfully
   */
  PLAYER_STATE_OPEN_COMPLETED,
  /** Player playing
   */
  PLAYER_STATE_PLAYING,
  /** Player paused
   */
  PLAYER_STATE_PAUSED,
  /** Player playback completed
   */
  PLAYER_STATE_PLAYBACK_COMPLETED,
  /** Player stopped
   */
  PLAYER_STATE_STOPPED = PLAYER_STATE_IDLE,
  /** Player pausing (internal)
   */
  PLAYER_STATE_PAUSING_INTERNAL = 50,
  /** Player stopping (internal)
   */
  PLAYER_STATE_STOPPING_INTERNAL,
  /** Player seeking state (internal)
   */
  PLAYER_STATE_SEEKING_INTERNAL,
  /** Player getting state (internal)
   */
  PLAYER_STATE_GETTING_INTERNAL,
  /** None state for state machine (internal)
   */
  PLAYER_STATE_NONE_INTERNAL,
  /** Do nothing state for state machine (internal)
   */
  PLAYER_STATE_DO_NOTHING_INTERNAL,
  /** Player failed
   */
  PLAYER_STATE_FAILED = 100,
};

/**
 * @brief Player error code
 *
 */
enum MEDIA_PLAYER_ERROR {
  /** No error
   */
  PLAYER_ERROR_NONE = 0,
  /** The parameter is incorrect
   */
  PLAYER_ERROR_INVALID_ARGUMENTS = -1,
  /** Internel error
   */
  PLAYER_ERROR_INTERNAL = -2,
  /** No resource error
   */
  PLAYER_ERROR_NO_RESOURCE = -3,
  /** Media source is invalid
   */
  PLAYER_ERROR_INVALID_MEDIA_SOURCE = -4,
  /** Unknown stream type
   */
  PLAYER_ERROR_UNKNOWN_STREAM_TYPE = -5,
  /** Object is not initialized
   */
  PLAYER_ERROR_OBJ_NOT_INITIALIZED = -6,
  /** Decoder codec not supported
   */
  PLAYER_ERROR_CODEC_NOT_SUPPORTED = -7,
  /** Video renderer is invalid
   */
  PLAYER_ERROR_VIDEO_RENDER_FAILED = -8,
  /** Internal state error
   */
  PLAYER_ERROR_INVALID_STATE = -9,
  /** Url not found
   */
  PLAYER_ERROR_URL_NOT_FOUND = -10,
  /** Invalid connection state
   */
  PLAYER_ERROR_INVALID_CONNECTION_STATE = -11,
  /** Insufficient buffer data
   */
  PLAY_ERROR_SRC_BUFFER_UNDERFLOW = -12,
};

/**
 * The type of the media stream.
 */
enum MEDIA_STREAM_TYPE {
  /** The stream type is unknown.
   */
  STREAM_TYPE_UNKNOWN = 0,
  /** Video.
   */
  STREAM_TYPE_VIDEO = 1,
  /** Audio.
   */
  STREAM_TYPE_AUDIO = 2,
  /** Subtitle.
   */
  STREAM_TYPE_SUBTITLE = 3,
};

/**
 * @brief Player event
 *
 */
enum MEDIA_PLAYER_EVENT {
  /** player seek begin
   */
  PLAYER_EVENT_SEEK_BEGIN = 0,
  /** player seek complete
   */
  PLAYER_EVENT_SEEK_COMPLETE = 1,
  /** player seek error
   */
  PLAYER_EVENT_SEEK_ERROR = 2,
  /** player video published
   */
  PLAYER_EVENT_VIDEO_PUBLISHED = 3,
  /** player audio published
   */
  PLAYER_EVENT_AUDIO_PUBLISHED = 4,
};

/**
 * Information of the media stream object.
 */
struct MediaStreamInfo { 
  /** The index of the stream in the media file. */
  int streamIndex;
  /** The type of the media stream: #MEDIA_STREAM_TYPE */
  MEDIA_STREAM_TYPE streamType;

  /** The name of the streaming codec. */
  char codecName[kMaxCodecNameLength];

  /** The language of the stream. */
  char language[kMaxCodecNameLength];

  /** The video frame rate (fps), if a video stream. */
  int videoFrameRate;

  /** The video bitrate (bps), if a video stream. */
  int videoBitRate;

  /** The width of the video (px), if a video stream. */
  int videoWidth;

  /** The height of the video (px), if a video stream. */
  int videoHeight;

  /** The audio sample rate (Hz), if an audio stream. */
  int audioSampleRate;

  /** The number of audio channels, if an audio stream. */
  int audioChannels;

  /** The number of bits per sample, if an audio stream. */
  int audioBitsPerSample;

  /** The duration (s) of this stream. */
  int64_t duration;};

/**
 * @brief Player Metadata type
 *
 */
enum MEDIA_PLAYER_METADATA_TYPE {
  /** data type unknown
   */
  PLAYER_METADATA_TYPE_UNKNOWN = 0,
  /** sei data
   */
  PLAYER_METADATA_TYPE_SEI = 1,
};

/**
 * The IAudioFrameObserver class.
 */
class IAudioFrameObserver {
 public:
  /**
   * The audio frame type.
   */
  enum AUDIO_FRAME_TYPE {
    /**
     * 0: The frame type is PCM.
     */
    FRAME_TYPE_PCM16 = 0,  // PCM 16bit little endian
  };
  /** 
   * The definition of AudioFrame.
   */
  struct AudioFrame {
    AUDIO_FRAME_TYPE type;
    /** 
     * The number of samples per channel in this frame.
     */
    int samplesPerChannel;
    /** 
     * The number of bytes per sample: Two for PCM 16.
     */
    int bytesPerSample;  
    /** 
     * The number of channels (data is interleaved, if stereo).
     */
    int channels; 
    /** 
     * The Sample rate.
     */
    int samplesPerSec;
    /** 
     * The pointer to the data buffer.
     */
    void* buffer;  
    /** 
     * The timestamp to render the audio data. Use this member to synchronize the audio renderer while 
     * rendering the audio streams.
     *
     * @note
     * This timestamp is for audio stream rendering. Set it as 0.
    */
    int64_t renderTimeMs;
    int avsync_type;
  };

 public:
  virtual ~IAudioFrameObserver() = default;

  /** 
   * Occurs when the recorded audio frame is received.
   * @param audioFrame The reference to the audio frame: AudioFrame.
   * @return
   * - true: The recorded audio frame is valid and is encoded and sent.
   * - false: The recorded audio frame is invalid and is not encoded or sent.
   */
  virtual bool onRecordAudioFrame(AudioFrame& audioFrame) = 0;
  /** 
   * Occurs when the playback audio frame is received.
   * @param audioFrame The reference to the audio frame: AudioFrame.
   * @return
   * - true: The playback audio frame is valid and is encoded and sent.
   * - false: The playback audio frame is invalid and is not encoded or sent.
   */
  virtual bool onPlaybackAudioFrame(AudioFrame& audioFrame) = 0;
  /** 
   * Occurs when the mixed audio data is received.
   * @param audioFrame The reference to the audio frame: AudioFrame.
   * @return
   * - true: The mixed audio data is valid and is encoded and sent.
   * - false: The mixed audio data is invalid and is not encoded or sent.
   */
  virtual bool onMixedAudioFrame(AudioFrame& audioFrame) = 0;
  /** 
   * Occurs when the playback audio frame before mixing is received.
   * @param uid ID of the remote user.
   * @param audioFrame The reference to the audio frame: AudioFrame.
   * @return
   * - true: The playback audio frame before mixing is valid and is encoded and sent.
   * - false: The playback audio frame before mixing is invalid and is not encoded or sent.
   */
  virtual bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame) = 0;
};
/**
 * The IVideoFrameObserver class.
 */
class IVideoFrameObserver {
 public:
  using VideoFrame = agora::media::VideoFrame;
  
 public:
  virtual ~IVideoFrameObserver() {}

  /** 
   * Occurs each time the SDK receives a video frame captured by the local camera.
   *
   * After you successfully register the video frame observer, the SDK triggers this callback each time 
   * a video frame is received. In this callback, you can get the video data captured by the local 
   * camera. You can then pre-process the data according to your scenarios.
   * 
   * After pre-processing, you can send the processed video data back to the SDK by setting the 
   * `videoFrame` parameter in this callback.
   * 
   * @param videoFrame A pointer to the video frame: VideoFrame
   * @return Determines whether to ignore the current video frame if the pre-processing fails:
   * - true: Do not ignore.
   * - false: Ignore, in which case this method does not sent the current video frame to the SDK.
  */
  virtual bool onCaptureVideoFrame(VideoFrame& videoFrame) = 0;
  /** 
   * Occurs each time the SDK receives a video frame sent by the remote user.
   * 
   * After you successfully register the video frame observer, the SDK triggers this callback each time a 
   * video frame is received. In this callback, you can get the video data sent by the remote user. You 
   * can then post-process the data according to your scenarios.
   * 
   * After post-processing, you can send the processed data back to the SDK by setting the `videoFrame`
   * parameter in this callback.
   *
   * @param uid ID of the remote user who sends the current video frame.
   * @param connectionId ID of the connection.
   * @param videoFrame A pointer to the video frame: VideoFrame
   * @return Determines whether to ignore the current video frame if the post-processing fails:
   * - true: Do not ignore.
   * - false: Ignore, in which case this method does not sent the current video frame to the SDK.
   */
  virtual bool onRenderVideoFrame(rtc::uid_t uid, rtc::conn_id_t connectionId,
                                  VideoFrame& videoFrame) = 0;

  virtual VIDEO_PIXEL_FORMAT getVideoPixelFormatPreference() {
      return VIDEO_PIXEL_I420; }
  virtual bool getRotationApplied() { return false; }
  virtual bool getMirrorApplied() { return false; }
};
}  // namespace media

namespace rtc {
/**
 * The audio route.
 */
enum AudioRoute
{
  /**
   * -1: The default audio route.
   */
  ROUTE_DEFAULT = -1,
  /**
   * The headset.
   */
  ROUTE_HEADSET,
  /**
   * The earpiece.
   */
  ROUTE_EARPIECE,
  /**
   * The headset with no microphone.
   */
  ROUTE_HEADSETNOMIC,
  /**
   * The speakerphone.
   */
  ROUTE_SPEAKERPHONE,
  /**
   * The loudspeaker.
   */
  ROUTE_LOUDSPEAKER,
  /**
   * The Bluetooth headset.
   */
  ROUTE_HEADSETBLUETOOTH
};
} // namespace rtc


}  // namespace agora
