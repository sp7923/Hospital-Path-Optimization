import pandas as pd
from scipy.spatial import distance_matrix
from IPython.display import display   
import requests
key = 'jJ5qJhg0qokreG8QF856q85jTVrO5hAi'
url = 'https://www.mapquestapi.com/geocoding/v1/address?key='+key

loc = ['Greams Lane, 21, Greams Rd, Thousand Lights, Chennai, Tamil Nadu 600006',

'35WV+2RW, 2nd Ave, F Block, Anna Nagar West Extension, Chennai, Tamil Nadu 600101'

,'No. 471, Madras Thiruvallur High Rd, Balaji Nagar, Thirumalai Square, Ambattur, Chennai, Tamil Nadu 600053'

,'Plot No, 64, Vanagaram-Ambattur Rd, Ayanambakkam, Ambattur Industrial Estate, Chennai, Tamil Nadu 600095'

,'Inside CMBT, Near Gate No: 8, Next to CMDA Estate Office,, Koyambedu, Chennai, Tamil Nadu 600107'

,'X42P+PVV, Pallavapuram, New Colony, Chromepet, Chennai, Tamil Nadu 600044'

,'W4F4+QF2, Kalyana Nagar, Tambaram, Chennai, Tamil Nadu 600045'

,'OMR Landmark Aravind theatre, 2/319, OMR Service Rd, Karapakkam, Chennai, Tamil Nadu 600097'

,'5/639, Rajiv Gandhi Salai, Tirumalai Nagar, Perungudi, Chennai, Tamil Nadu 600096'

,'No 320, Anna Salai, Sadras, Nandanam, Chennai, Tamil Nadu 600035'

,'Teynampet, 6, Cenotaph Rd, Chennai, Tamil Nadu 600035']

# loc = ['khagesiyamau, sitapur , uttar pradesh 261001']

latitude = []
longitude = []

for str in loc :
    main_url = url  + '&location=' +str
    r = requests.get(main_url)
    data = r.json()['results'][0]
    # data = r.json()
    location = data['locations'][0]
    lat = location['latLng']['lat']
    lon = location['latLng']['lng']
    latitude.append(lat)
    longitude.append(lon)
    # print(data);    

# for i in range(len(latitude)):
# print(latitude)
# print(longitude)
coordinates=list(zip(latitude,longitude))
ctys = ['Thousand Lights', 'Anna Nagar West Extension', 'Ambattur','Ambattur Industrial Estate','Koyambedu','Chromepet','Tambaram','Karapakkam','Perungudi','Nandanam','Cenotaph Rd']
df = pd.DataFrame(coordinates, columns=['xcord', 'ycord'], index=ctys)
display(df)
# res=pd.DataFrame(distance_matrix(df.values, df.values), index=df.index, columns=df.index)      
# display(res)
# latitude = [13.06506, 13.09517, 38.89037, 13.09261, 13.07102, 12.95112, 38.89037, 12.91541, 12.95915, 13.02789, 13.03332]
# longitude = [80.2553, 80.19438, -77.03196, 80.1464, 80.20358, 80.13731, -77.03196, 80.22963, 80.24442, 80.23516, 80.24592]

# slopes =[]
# x = latitude[0]
# y = longitude[0]
# for i in range(1,len(latitude)):
#     slope = (x-latitude[i])/(y-longitude[i])
#     slopes.append(slope)

# print(slopes)