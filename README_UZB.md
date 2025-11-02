# BrickGame Tetris

Qisqa mazmuni: ushbu loyihada siz tuzilmaviy yondashuv yordamida “Tetris” o'yinini C dasturlash tilida amalga oshirasiz.

💡 **Ushbu loyiha haqida biz bilan fikr-mulohazalaringizni baham ko’rish uchun [bu yerni bosing](https://new.oprosso.net/p/4cb31ec3f47a4596bc758ea1861fb624)**. Bu anonim bo’lib, jamoamizga ta’limni yaxshilashga yordam beradi. Loyihani tugatgandan so'ng darhol so'rovnomani to'ldirishni tavsiya qilamiz.

## Mundarija

- [BrickGame Tetris](#brickgame-tetris)
  - [Mundarija](#mundarija)
  - [Kirish](#kirish)
  - [Chapter I](#chapter-i)
  - [Umumiy ma'lumot](#umumiy-malumot)
    - [BrickGame](#brickgame)
    - [Tetris tarixi](#tetris-tarixi)
    - [So’nggi avtomatlar](#songgi-avtomatlar)
    - [Frogger](#frogger)
    - [Tetris](#tetris)
  - [Chapter II](#chapter-ii)
  - [Loyiha talablari](#loyiha-talablari)
    - [1-qism. Asosiy topshiriq](#1-qism-asosiy-topshiriq)
    - [2-qism. Qo'shimcha. O'yindagi ochkolarni hisoblash va rekord](#2-qism-qoshimcha-oyindagi-ochkolarni-hisoblash-va-rekord)
    - [3-qism. Qo'shimcha. Darajalar mexanikasi](#3-qism-qoshimcha-darajalar-mexanikasi)


## Kirish

“Tetris” o'yinini amalga oshirish uchun loyiha ikki qismdan iborat bo'lishi kerak: o'yin ishi mantig'ini amalga oshiradigan va kelajakda turli GUI-larga ulanishi mumkin bo’lgan kutubxonalar hamda terminal interfeysi. Kutubxona ishi mantig'i so’nggi avtomatlar yordamida amalga oshirilishi kerak, ularning mumkin bo'lgan tavsiflaridan biri quyida keltirilgan.

## Chapter I 
## Umumiy ma'lumot
### BrickGame

BrickGame – bir nechta o'rnatilgan o'yinlarga ega bo’lgan 90-yillardagi mashhur portativ konsol bo'lib, u Xitoyda ishlab chiqilgan. O'yin dastlab SSSRda ishlab chiqilgan va Nintendo tomonidan GameBoy platformasi doirasida chiqarilgan “Tetris” o'yinining nusxasi edi, ammo vaqt o'tishi bilan qo'shib borilgan ko'plab boshqa o'yinlarni ham o'z ichiga olgandi. Konsolda 10 x 20 o'lchamdagi o'yin maydoni bo'lgan kichik ekrancha bo’lib, bu "piksellar" matritsasini ifodalardi. Maydonning o'ng tomonida joriy o'yin holati, rekordlar va boshqa qo'shimcha ma'lumotlarning raqamli ko'rsatkichini o’z ichiga olgan tablo bor edi. BrickGame-dagi eng keng tarqalgan o'yinlar: tetris, tankalar, poyga, frogger va iloncha edi.

![BrickGameConsole](misc/images/brickgame-console.jpg)

### Tetris tarixi

"Tetris" Aleksey Pajitnov tomonidan 1984 yil 6 iyunda Elektronika-60 kompyuterida yozilgan. O'yin to'rt kvadratdan iborat geometrik tetramino figuralaridan foydalanishga asoslangan boshqotirma edi. O'yinning birinchi tijorat versiyasi 1987 yilda Amerikada chiqarilgan. Keyingi yillarda Tetris mobil telefonlar, kalkulyatorlar va shaxsiy cho’ntak kompyuterlarini o'z ichiga olgan turli xil qurilmalarga ko'chirildi.

Game Boy o'yin konsoli va NES video pristavkasi uchun “Tetris”ning amalga oshirilishi eng katta mashhurlikka erishdi. Ammo bundan tashqari, o'yinning turli xil versiyalari mavjud. Misol uchun, uch o’lchamli figuralarga ega bo'lgan versiya yoki duel versiyasi mavjud bo'lib, unda ikkita o'yinchi bir xil figuralarni qabul qiladi va bir-biridan ochkolar bo'yicha o’zib ketishga harakat qiladi.

### So’nggi avtomatlar

Algoritmlar nazariyasidagi so’nggi avtomat (SA) – matematik abstraksiya, bitta kirish, bitta chiqishga ega bo'lgan va vaqtning har bir lahzasida ko'plab mumkin bo'lganlardan bitta holatda bo'luvchi diskret qurilma modelidir.

SA ishlayotganda, kirish ta'sirlari kirishda ketma-ket qabul qilinadi, chiqishda esa SA chiqish signallarini hosil qiladi. SAning bir ichki holatidan ikkinchisiga o'tishi nafaqat tashqi ta'sir, balki o'z-o'zidan ham sodir bo'lishi mumkin.

SA ma'lum muammolarni hal qilishga imkon beruvchi algoritmlarni tavsiflash uchun, shuningdek, deyarli har qanday jarayonni modellashtirish uchun ishlatilishi mumkin. Ba'zi misollar:

- O'yinlar uchun sun'iy intellekt mantig’i;
- Sintaktik va leksik tahlil;
- Murakkab amaliy tarmoq protokollari;
- Ma'lumotlarni oqimli qayta ishlash.

Quyida BrickGamedan bir nechta o'yinlarning o'yin mantig’ini formallashtirish uchun SA dan foydalanish misollari keltirilgan.

### Frogger

![Frogger](misc/images/frogger-game.png)

“Frogger” Brickgame konsollarida chiquvchi eng so'nggi o'yinlardan biridir. O'yinda o'yin maydonchasi bo'lib, u bo'ylab xodalar harakatlanadi va ular ustidan sakrab o'tish orqali o'yinchi qurbaqani bir sohildan boshqasiga ko'chirishi kerak bo’ladi. Agar o'yinchi suvga tushib qolsa yoki qurbaqa o'yin maydoni chegarasidan chiqsa, qurbaqa o'ladi. O'yinchi qurbaqani boshqa sohilga olib kelganda yoki oxirgi qurbaqa ham o'lganida, o'yin tugaydi.

Ushbu o'yinning mantig'ini formallashtirish uchun so’nggi avtomatning quyidagi versiyasini tasavvur qilish mumkin:

![Frogger1](misc/images/frogger.jpg)

Ushbu SA quyidagi holatlarga ega:

- Start – o'yin o'yinchi o'ynashga tayyorlik tugmasini bosishini kutadigan holat.
- Spavn – keyingi qurbaqa yaratiluvchi holat.
- Harakatlanish – foydalanuvchi tomonidan kiritilgan ma'lumotlar qayta ishlanuvchi asosiy o'yin holati: qurbaqani chiziq bo'ylab chapga/o'ngga siljitish yoki oldinga/orqaga sakrash.
- Siljish – taymer muddati tugagandan so'ng yuzaga keladigan holat, bunda chiziqlardagi barcha obyektlar qurbaqa bilan birga o'ngga siljiydi.
- To’qnashuv – bu qurbaqa sakrashdan keyin suvga tushib qolganda yoki xodalar harakatlanib, qurbaqa o‘yin maydonidan tashqariga chiqib qolganda sodir bo‘ladigan holat.
- Boshqa sohilga erishildi – qurbaqa yuqoridagi boshqa sohilga yetib kelganida yuzaga keladigan holat.
- O'yin tugadi – boshqa sohilga yetib borganidan keyin yoki oxirgi qurbaqaning ham o'limidan keyin yuzaga keladigan holat.

SA yordamida froggerni amalga oshirish misolini code-samples papkasida topishingiz mumkin.

### Tetris

![Tetris](misc/images/tetris-game.png)

Tetris, aftidan, Brickgame konsoli uchun eng mashhur o'yinlardan biridir. Konsolning o'zi ko'pincha Tetris deb ham ataladi. O'yinning maqsadi – o'yin tomonidan yuzaga keltiriluvchi bloklardan qatorlar qurish orqali ochko to'plashdir. O'yin tomonidan yaratilgan galdagi blok pastki chegaraga yetmaguncha yoki boshqa blok bilan to'qnashmaguncha o'yin maydonidan pastga tusha boshlaydi. Foydalanuvchi qatorlar hosil qilishga harakat qilib, shakllarni aylantirishi va ularni gorizontal ravishda siljitishi mumkin. To'ldirilgandan so'ng, qator yo'q bo’ladi, o'yinchi ochko oladi va to'ldirilgan qator ustidagi bloklar pastga siljiydi. Navbatdagi shakl eng yuqori qatorda to'xtaganda o'yin tugaydi.

Ushbu o'yinning mantig'ini formallashtirish uchun so’nggi avtomatning quyidagi variantini taqdim etish mumkin:

![Tetris1](misc/images/tetris.png)

Ushbu SA quyidagi holatlardan iborat:
- Start – o'yin o'yinchi o'ynashga tayyorlik tugmasini bosishini kutadigan holat.
- Spavn – keyingi blokni yaratish va spavn uchun keyingi blokni tanlashdagi o'yin holati.
- Harakatlanish — foydalanuvchining kiritishni qayta ishlashi bilan bog’liq asosiy oʻyin holati: bloklarni aylantirish/gorizontal ravishda bloklarni harakatlantirish.
- Siljish – taymer muddati tugagandan so'ng o'yin o’tadigan holat. Unda joriy blok bir daraja pastga siljiydi.
- Ulanish – joriy blok allaqachon tushib bo’lgan bloklarga yoki yerga “tekkanidan” keyin o‘yin o’tadigan holat. Agar to'ldirilgan qator hosil bo'lsa, u yo'qolib, qolgan bloklar pastga siljiydi. Agar blok eng yuqori qatorda to'xtasa, o'yin "o'yin tugadi" holatiga o'tadi.
- O'yin tugadi – O'yin tugadi.

## Chapter II
## Loyiha talablari

### 1-qism. Asosiy topshiriq

Siz BrickGame v1.0 aka Tetris dasturini amalga oshirishingiz kerak:
- Dastur gcc kompilyatoridan foydalangan holda C11 standartidagi C tilida ishlab chiqilishi kerak.
- Dastur ikki qismdan iborat bo'lishi kerak: Tetris o'yinining mantig’ini amalga oshiradigan kutubxonalar va `ncurses` kutubxonasi yordamida terminal interfeysi.
- O'yin mantig'ini formallashtirish uchun so’nggi avtomatdan foydalanish kerak.
- Kutubxona, kirishda foydalanuvchi tomonidan kiritiluvchilarni qabul qiladigan funksiyaga va har safar u o'zgarganda o'yin maydonining joriy holatini tavsiflovchi matritsa hosil qiluvchi funksiyaga ega bo'lishi kerak.
- Dastur kutubxonasi kodi `src/brick_game/tetris` papkasida joylashgan bo'lishi kerak.
- Dastur interfeysi kodi `src/gui/cli` papkasida joylashgan bo'lishi kerak
- Dastur tuzilmasi GNU dasturlari uchun standart maqsadlar to'plamiga ega Makefile yordamida sozlanishi kerak: all, install, uninstall, clean, dvi, dist, test, gcov_report. O'rnatish boshqa har qanday ixtiyoriy katalogda amalga oshirilishi kerak.
- Dastur tuzilgan dasturlash tamoyillari asosida ishlab chiqilishi kerak.
- Kod yozishda C++ uchun Google Style ((havola)[(https://google.github.io/styleguide/cppguide.html)]) ga amal qiling.
- Kutubxona, `check` kutubxonasidan foydalangan holda unit testlar bilan qoplangan bo'lishi kerak (testlar ОС Darwin/Ubuntu ga o'tkazilishi kerak). Kutubxonaning testlar tomonidan o'yin mantig'i bilan qamrab olinishi kamida 80 foiz bo'lishi kerak.
- O'yinda quyidagi mexanika mavjud bo'lishi kerak:
  - Shakllarni aylantirish;
  - Shaklni gorizontal ravishda siljitish;
  - Shakllar tushishini tezlashtirish (tugmachani bosganda, shakl oxirigacha pastga siljiydi);
  - Keyingi shaklni ko'rsatish;
  - To'ldirilgan qatorlar yo’q bo’lishi;
  - O'yin maydonining yuqori chegarasiga yetganda o'yinning tugashi;
  - O'yin quyidagi rasmda ko'rsatilgan barcha turdagi shakllarni o'z ichiga olishi kerak.
- Boshqarish uchun jismoniy konsolda taqdim etilgan barcha tugmalar qo‘llab-quvvatlanishini qo’shing:
  - O'yin boshlanishi,
  - Pauza,
  - O'yinni tugatish,
  - Chapga qaratilgan strelka – shaklning chapga siljishi,
  - O'ngga qaratilgan strelka – shaklning o'ngga siljishi,
  - Pastga qaratilgan strelka – shaklning tushishi,
  - Yuqoriga qaratilgan strelka – bu o'yinda ishlatilmaydi,
  - Harakat (shaklning aylanishi).
- O'yin maydoni konsol o'yin maydonining o'lchamlariga mos kelishi kerak: kengligi o'n "piksel" va balandligi yigirma "piksel".
- Shakl maydonning pastki chegarasiga yetib borganidan keyin yoki boshqa shaklga tekkanidan keyin to‘xtashi kerak. Shundan so'ng, prevyuda ko'rsatilgan keyingi shakl hosil bo'lishi lozim.
- Kutubxona interfeysi [bu yerda](./materials/library-specification_UZB.md) joylashgan tavsifga mos kelishi kerak.
- Foydalanuvchi interfeysi o'yin maydonini va qo'shimcha ma'lumotlarni ko'rsatishni qo'llab-quvvatlashi kerak.
- Foydalanilayotgan SAni (uning holatlari va barcha mumkin bo'lgan o'tishlarini) tavsiflovchi har qanday formatdagi diagramma tayyorlang.

Ishlatiluvchi shakllar:

![shakllar](misc/images/tetris-pieces.png)

### 2-qism. Qo'shimcha. O'yindagi ochkolarni hisoblash va rekord

O'yinga quyidagi mexanikani qo'shing:

- ochkolarni hisoblash;
- ochkolarning maksimal miqdorini saqlash.

Ushbu ma'lumot yon paneldagi foydalanuvchi interfeysi tomonidan uzatilishi va chiqarilishi kerak. Ochkolarning maksimal miqdori faylda yoki o'rnatiluvchi ma’lumotlar bazasini boshqarish tizimida saqlanishi va dasturni ishga tushirish oralig'ida saqlanishi kerak.

Agar foydalanuvchi o'yin davomida joriy maksimal ochko miqdori ko’rsatkichidan oshib ketsa, maksimal ochko miqdori o'yin davomida o'zgarishi kerak.

Ochkolarni hisoblash quyidagi tarzda amalga oshiriladi:

- 1 qator – 100 ochko;
- 2 qator – 300 ochko;
- 3 qator – 700 ochko;
- 4 qator – 1500 ochko.

### 3-qism. Qo'shimcha. Darajalar mexanikasi

O'yinga darajadagi mexanikani qo'shing. Har safar o'yinchi 600 ochko to'plaganida, daraja 1 ga oshadi. Darajani oshirish shakllar tezligini oshiradi. Maksimal darajalar soni – 10.
