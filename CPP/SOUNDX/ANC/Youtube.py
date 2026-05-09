from googleapiclient.discovery import build

# Replace with the API key you generated in the Google Cloud Console
API_KEY = 'YOUR_API_KEY'

# Initialize the YouTube API client
youtube = build('youtube', 'v3', developerKey=API_KEY)

def search_and_get_details(query, max_results=3):
    print(f"Searching YouTube for: '{query}'...\n")
    
    # 1. Search for videos matching the query
    search_request = youtube.search().list(
        q=query,
        part='snippet',
        maxResults=max_results,
        type='video' # Ensures we only get videos back, not channels or playlists
    )
    search_response = search_request.execute()

    # Extract the Video IDs from the search results
    video_ids = []
    for item in search_response.get('items', []):
        video_ids.append(item['id']['videoId'])

    if not video_ids:
        print("No videos found.")
        return

    # 2. Request detailed statistics for those specific Video IDs
    video_request = youtube.videos().list(
        id=','.join(video_ids),
        part='snippet,statistics' # Requesting both text details and number stats
    )
    video_response = video_request.execute()

    # Print out the gathered data
    for video in video_response.get('items', []):
        title = video['snippet']['title']
        channel = video['snippet']['channelTitle']
        views = video['statistics'].get('viewCount', '0')
        likes = video['statistics'].get('likeCount', '0')
        
        print(f"Title: {title}")
        print(f"Channel: {channel}")
        print(f"Views: {views} | Likes: {likes}")
        print("-" * 40)

# Run the function
if __name__ == '__main__':
    # You can search for music, coding tutorials, or any other topic
    search_and_get_details("lofi hip hop radio")