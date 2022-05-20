import urllib.request,urllib.error
import re
import bs4
import xlwt
def main():
    url = "https://movie.douban.com/chart"
    path = "豆瓣新电影top250"
    html = AskURL(url)
    # print(type(html))
    findinfo(html)
    # savedata()

# 爬取网站返回源代码html
def AskURL(url):
    #url = "https://movie.douban.com/chart"
    headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.107 Safari/537.36"}
    req = urllib.request.Request(url = url, headers = headers)
    res = urllib.request.urlopen(req)
    html = res.read().decode("utf - 8")
    return html

datalist = []
findname = re.compile(r'title="(.*?)">')
findlink = re.compile(r'href="(.*?)">')
finddir = re.compile(r'<p class="pl">(.*?)</p>')
findrank = re.compile(r'<span class="rating_nums">(.*?)</span>')

def findinfo(html):
    soup = bs4.BeautifulSoup(html, "html.parser")
    for item in soup.find_all("tr", class_ = "item"):
        item = str(item)
        print(item)
        # data = []
        # #影片名字
        # name = re.findall(findname, item)[0]
        # data.append(name)
        # # print(name)
        # #影片链接
        # link = re.findall(findlink, item)[1]
        # # print(link)
        # data.append(link)
        #
        # #影片导演，演员
        # diract = re.findall(finddir, item)[0]
        # data.append(diract)
        # # print(diract)
        # # break
        #
        # #影片评分
        # rank = re.findall(findrank, item)
        # # print(rank)
        # data.append(rank)
        # # print(data)
        # datalist.append(data)
    # print(len(datalist))
    # print(len(data))

# def savedata( ):
#     workbook = xlwt.Workbook(encoding="utf - 8")
#     sheet = workbook.add_sheet("sheet1")
#     row = ("电影名字", "电影链接", "导演和演员", "评分")
#     for i in range(0, 4):
#         sheet.write(0,i, row[i])
#     for i in range(1, 11):
#         data = datalist[i - 1]
#         for j in range(0, 4):
#             sheet.write(i,j, data[j])
#     print(datalist)
#     workbook.save("豆瓣新影片top.xls")







if __name__ == '__main__':
    main()
