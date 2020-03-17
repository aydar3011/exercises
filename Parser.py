import requests
import csv
from bs4 import BeautifulSoup
from bs4 import BeautifulStoneSoup
import wget

def csvwrite(result):
    with open('products.csv', 'w', encoding='utf-8') as b:
        fieldnames=['_MODEL_','_NAME_', '_IMAGE_','_MANUFACTURER_','_MAIN_CATEGORY_','_DESCRIPTION_','_ATTRIBUTES_']
        writer = csv.DictWriter(b, delimiter=';', fieldnames=fieldnames)
        writer.writeheader()
        for line in result:
            writer.writerow(line)
        b.close()


def parsingProducts(url):
    results = []
    r = requests.get(url)

    soup = BeautifulSoup(r.text, 'lxml')

    tovdet = soup.find('main', {'class': 'general-content'}).find('section', {'class': 'tovar-detail'})

    try:
        hleb = tovdet.find('div', {'class': 'top-row'}).find('section', {'class': 'site__col-middle'}).find('div', {'class': 'breadcrumbs'}).find('ul', {'class': 'breadcrumbs__list'}).find_all('li')
    except AttributeError:
        return -1
    breadcrumb = ''

    for i in range(1,len(hleb)):
        if i != len(hleb)-1:
            breadcrumb += hleb[i].find('a').text + '|'
        else:
            breadcrumb += hleb[i].find('a').text

    mainContainer = tovdet.find('div', {'class': 'tovar-detail__content'}).find('div', {'class': 'main-container'})
    name = mainContainer.find('div', {'class': 'tovar-detail__row-1'}).find('h2').text.strip() + ' '
    name += mainContainer.find('div', {'class': 'tovar-detail__title'}).find('h1').text
    tovarDetailContentBlock = mainContainer.find('div', {'class': 'tovar-detail__content-block'})
    image = 'https://www.tinko.ru' + tovarDetailContentBlock.find('div', {'class': 'tovar-detail__image'}).find('img').get('src')
    trash,artikul = tovarDetailContentBlock.find('div', {'class': 'tovar-detail__row-1'}).find('span', {'class': 'tovar-detail__code'}).findAll('span')
    manufacturer = tovarDetailContentBlock.find('span', {'class': 'tovar-detail__creator'}).find('a').text
    manufacturer = manufacturer.strip()
    sd = tovarDetailContentBlock.find('div', {'class': 'tovar-detail__short-description'}).find_all('span')
    description=''
    prices = tovarDetailContentBlock.find('ul', {'class': 'tovar-detail__prices'}).find_all('li')
    price_opt = ''
    special = ''
    if len(prices) == 1:
        price = float(prices[0].find('div', {'class': 'old-normal-price'}).find('span').text.strip().replace(' ', '').replace(',', '.'))
        x = float(prices[0].find('div', {'class': 'tovar-detail__price'}).find  ('span').text.strip().replace(' ', '').replace(',', '.'))
        special = '1,1,'+str(x)+'\n2,1,'+str(x)
    else:
        if prices[0].find('div', {'class': 'tovar-detail__price'}).find('span').text.strip() != 'Цена по запросу':
            price = float(prices[0].find('div', {'class': 'tovar-detail__price'}).find('span').text.strip().replace(' ','').replace(',','.'))
            price_opt = float(prices[1].find('div', {'class': 'tovar-detail__price'}).find('span').text.strip().replace(' ','').replace(',','.'))
        else:
            price = ''
            price_opt = ''
    for item in sd:
        if(item.text != 'Краткое описание:'):
            description += ('<span>' + item.text.strip()+'</span>')

    tip = 'Характеристики|'
    attributes=''

    try:
        ds = mainContainer.find('div', {'class': 'tabs-content__item tovar-detail__tab tovar-detail__description'}).find('div', {'class': 'tabs-content__item-toggle'})
        description += str(ds)
    except AttributeError:
        description += ''

    try:
        techSpecs = mainContainer.find('div', {'class': 'tabs-content__item tovar-detail__tab tovar-detail__th'}).find('ul', {'class': 'characteristics_mobile'}).find_all('li')
        for data in techSpecs:
            firstSpan, secondSpan = data.findAll('span')
            attributes += (tip + firstSpan.text + '|' + secondSpan.text+'\n')
    except AttributeError:
        attributes = ''

    stockst = mainContainer.find('span', {'class': 'with-hint'}).text
    if stockst == 'В наличии':
        stock = 7
    else:
        stock = 8

    results.append({
        '_MODEL_': artikul.text,
        '_NAME_': name,
        '_IMAGE_': image,
        '_CATEGORY_': breadcrumb,
        '_DESCRIPTION_': description,
        '_MANUFACTURER_': manufacturer,
        '_ATTRIBUTES_': attributes,
        '_QUANTITY_': 1000,
        '_STATUS_': 1,
        '_STOCK_STATUS_ID_': stock,
        '_PRICE_': price,
        '_CUSTOM_PRICE_WHOLESALE_': price_opt,
        '_SPECIAL_': special

    })
    print(artikul.text)
    return results


with open('products.csv', 'w', encoding='utf-8') as b:
    fieldnames = ['_MODEL_', '_NAME_', '_IMAGE_', '_MANUFACTURER_', '_CATEGORY_',
                  '_DESCRIPTION_', '_ATTRIBUTES_', '_QUANTITY_', '_STATUS_', '_STOCK_STATUS_ID_',
                  '_PRICE_', '_CUSTOM_PRICE_WHOLESALE_', '_SPECIAL_']
    writer = csv.DictWriter(b, delimiter=';', fieldnames=fieldnames)
    writer.writeheader()

with open(wget.download('https://tinko.ru/sitemap.xml'), 'r', encoding='utf-8') as w:
    a = w.read()
urls = BeautifulStoneSoup(a).find_all('loc')
for url in urls:
    if url.text.find('https://www.tinko.ru/catalog/product/') == 0:
        demo = (parsingProducts(url.text.strip()))
        if demo != -1:
            with open('products.csv', 'a', encoding='utf-8') as b:
                fieldnames = ['_MODEL_', '_NAME_', '_IMAGE_', '_MANUFACTURER_', '_CATEGORY_',
                                          '_DESCRIPTION_', '_ATTRIBUTES_', '_QUANTITY_', '_STATUS_', '_STOCK_STATUS_ID_',
                                          '_PRICE_', '_CUSTOM_PRICE_WHOLESALE_', '_SPECIAL_']
                writer = csv.DictWriter(b, delimiter=';', fieldnames=fieldnames)
                writer.writerow(demo[0])




