# -*- coding: utf-8 -*-
import sys
sys.stdout.reconfigure(encoding='utf-8')

with open(r"F:\TVTEST PROJECT\TVTest-develop\src\EpgUtil.cpp", 'r', encoding='utf-8') as f:
    text = f.read()

replacements = {
    'StringCopy(szEndTime, TEXT("(終了未定)"));':
        'StringCopy(szEndTime, TEXT("(Fin por determinar)"));',
    
    # Géneros y subgéneros
    'TEXT("ニュース／報道"),': 'TEXT("Noticias / Actualidad"),',
    'TEXT("定時・総合"),': 'TEXT("General / Regular"),',
    'TEXT("天気"),': 'TEXT("Clima y tiempo"),',
    'TEXT("特集・ドキュメント"),': 'TEXT("Especiales / Documental"),',
    'TEXT("政治・国会"),': 'TEXT("Política / Congreso"),',
    'TEXT("経済・市況"),': 'TEXT("Economía / Finanzas"),',
    'TEXT("海外・国際"),': 'TEXT("Internacional"),',
    'TEXT("解説"),': 'TEXT("Análisis"),',
    'TEXT("討論・会談"),': 'TEXT("Debate / Entrevistas"),',
    'TEXT("報道特番"),': 'TEXT("Edición especial"),',
    'TEXT("ローカル・地域"),': 'TEXT("Regional / Local"),',
    'TEXT("交通"),': 'TEXT("Tráfico"),',
    'TEXT("その他")': 'TEXT("Otros")',
    
    'TEXT("スポーツ"),': 'TEXT("Deportes"),',
    'TEXT("スポーツニュース"),': 'TEXT("Noticias deportivas"),',
    'TEXT("野球"),': 'TEXT("Béisbol"),',
    'TEXT("サッカー"),': 'TEXT("Fútbol"),',
    'TEXT("ゴルフ"),': 'TEXT("Golf"),',
    'TEXT("その他の球技"),': 'TEXT("Otros deportes con pelota"),',
    'TEXT("相撲・格闘技"),': 'TEXT("Lucha / Artes marciales"),',
    'TEXT("オリンピック・国際大会"),': 'TEXT("Juegos Olímpicos / Torneos"),',
    'TEXT("マラソン・陸上・水泳"),': 'TEXT("Maratón / Atletismo / Natación"),',
    'TEXT("モータースポーツ"),': 'TEXT("Automovilismo / Deportes de motor"),',
    'TEXT("マリン・ウィンタースポーツ"),': 'TEXT("Deportes náuticos e invernales"),',
    'TEXT("競馬・公営競技"),': 'TEXT("Hípica / Carreras"),',

    'TEXT("情報／ワイドショー"),': 'TEXT("Variedades / Magacín"),',
    'TEXT("芸能・ワイドショー"),': 'TEXT("Espectáculos"),',
    'TEXT("ファッション"),': 'TEXT("Moda y estilo"),',
    'TEXT("暮らし・住まい"),': 'TEXT("Hogar y estilo de vida"),',
    'TEXT("健康・医療"),': 'TEXT("Salud y medicina"),',
    'TEXT("ショッピング・通販"),': 'TEXT("Compras / Teletienda"),',
    'TEXT("グルメ・料理"),': 'TEXT("Gastronomía y cocina"),',
    'TEXT("イベント"),': 'TEXT("Eventos"),',
    'TEXT("番組紹介・お知らせ"),': 'TEXT("Avances y anuncios"),',

    'TEXT("ドラマ"),': 'TEXT("Series / Telenovelas / Drama"),',
    'TEXT("国内ドラマ"),': 'TEXT("Series nacionales"),',
    'TEXT("海外ドラマ"),': 'TEXT("Series internacionales"),',
    'TEXT("時代劇"),': 'TEXT("Drama histórico"),',

    'TEXT("音楽"),': 'TEXT("Música"),',
    'TEXT("国内ロック・ポップス"),': 'TEXT("Pop / Rock nacional"),',
    'TEXT("海外ロック・ポップス"),': 'TEXT("Pop / Rock internacional"),',
    'TEXT("クラシック・オペラ"),': 'TEXT("Clásica / Ópera"),',
    'TEXT("ジャズ・フュージョン"),': 'TEXT("Jazz / Fusión"),',
    'TEXT("歌謡曲・演歌"),': 'TEXT("Música tradicional / Popular"),',
    'TEXT("ライブ・コンサート"),': 'TEXT("Conciertos en vivo"),',
    'TEXT("ランキング・リクエスト"),': 'TEXT("Listas de éxitos / Rankings"),',
    'TEXT("カラオケ・のど自慢"),': 'TEXT("Karaoke / Concursos de canto"),',
    'TEXT("民謡・邦楽"),': 'TEXT("Folclore / Música folclórica"),',
    'TEXT("童謡・キッズ"),': 'TEXT("Música infantil"),',
    'TEXT("民族音楽・ワールドミュージック"),': 'TEXT("Música del mundo"),',

    'TEXT("バラエティ"),': 'TEXT("Entretenimiento / Show"),',
    'TEXT("クイズ"),': 'TEXT("Concursos / Preguntas"),',
    'TEXT("ゲーム"),': 'TEXT("Juegos"),',
    'TEXT("トークバラエティ"),': 'TEXT("Talk shows"),',
    'TEXT("お笑い・コメディ"),': 'TEXT("Humor / Comedia"),',
    'TEXT("音楽バラエティ"),': 'TEXT("Variedades musicales"),',
    'TEXT("旅バラエティ"),': 'TEXT("Viajes y aventura"),',
    'TEXT("料理バラエティ"),': 'TEXT("Programas de cocina"),',

    'TEXT("映画"),': 'TEXT("Cine / Películas"),',
    'TEXT("洋画"),': 'TEXT("Cine internacional"),',
    'TEXT("邦画"),': 'TEXT("Cine nacional"),',
    'TEXT("アニメ"),': 'TEXT("Animación"),',

    'TEXT("アニメ／特撮"),': 'TEXT("Animación / Efectos"),',
    'TEXT("国内アニメ"),': 'TEXT("Animación nacional"),',
    'TEXT("海外アニメ"),': 'TEXT("Animación internacional"),',
    'TEXT("特撮"),': 'TEXT("Efectos especiales / Tokusatsu"),',

    'TEXT("ドキュメンタリー／教養"),': 'TEXT("Documentales / Cultura"),',
    'TEXT("社会・時事"),': 'TEXT("Sociedad y actualidad"),',
    'TEXT("歴史・紀行"),': 'TEXT("Historia y viajes"),',
    'TEXT("自然・動物・環境"),': 'TEXT("Naturaleza y medio ambiente"),',
    'TEXT("宇宙・科学・医学"),': 'TEXT("Ciencia, espacio y tecnología"),',
    'TEXT("カルチャー・伝統文化"),': 'TEXT("Cultura y tradiciones"),',
    'TEXT("文学・文芸"),': 'TEXT("Literatura y artes"),',
    'TEXT("ドキュメンタリー全般"),': 'TEXT("Documentales generales"),',
    'TEXT("インタビュー・討論"),': 'TEXT("Entrevistas y debates"),',

    'TEXT("劇場／公演"),': 'TEXT("Teatro / Espectáculos"),',
    'TEXT("現代劇・新劇"),': 'TEXT("Teatro contemporáneo"),',
    'TEXT("ミュージカル"),': 'TEXT("Musicales"),',
    'TEXT("ダンス・バレエ"),': 'TEXT("Danza y ballet"),',
    'TEXT("落語・演芸"),': 'TEXT("Comedia en vivo / Monólogos"),',
    'TEXT("歌舞伎・古典"),': 'TEXT("Teatro clásico"),',

    'TEXT("趣味／教育"),': 'TEXT("Aficiones / Educación"),',
    'TEXT("旅・釣り・アウトドア"),': 'TEXT("Viajes, pesca y aire libre"),',
    'TEXT("園芸・ペット・手芸"),': 'TEXT("Jardinería, mascotas y manualidades"),',
    'TEXT("音楽・美術・工芸"),': 'TEXT("Arte, música y artesanía"),',
    'TEXT("囲碁・将棋"),': 'TEXT("Ajedrez / Juegos de mesa"),',
    'TEXT("麻雀・パチンコ"),': 'TEXT("Juegos de azar"),',
    'TEXT("車・オートバイ"),': 'TEXT("Motor y motociclismo"),',
    'TEXT("コンピュータ・TVゲーム"),': 'TEXT("Informática y videojuegos"),',
    'TEXT("会話・語学"),': 'TEXT("Idiomas"),',
    'TEXT("幼児・小学生"),': 'TEXT("Infantil y primaria"),',
    'TEXT("中学生・高校生"),': 'TEXT("Secundaria y bachillerato"),',
    'TEXT("大学生・受験"),': 'TEXT("Universidad / Exámenes"),',
    'TEXT("生涯学習・資格"),': 'TEXT("Capacitación y cursos"),',
    'TEXT("教育問題"),': 'TEXT("Debate educativo"),',

    'TEXT("福祉"),': 'TEXT("Bienestar social"),',
    'TEXT("高齢者"),': 'TEXT("Tercera edad"),',
    'TEXT("障害者"),': 'TEXT("Discapacidad e inclusión"),',
    'TEXT("社会福祉"),': 'TEXT("Asistencia social"),',
    'TEXT("ボランティア"),': 'TEXT("Voluntariado"),',
    'TEXT("手話"),': 'TEXT("Lengua de señas"),',
    'TEXT("文字(字幕)"),': 'TEXT("Subtitulado (CC)"),',
    'TEXT("音声解説"),': 'TEXT("Audiodescripción"),',
}

cnt = 0
for k, v in replacements.items():
    if k in text:
        text = text.replace(k, v)
        cnt += 1
    else:
        print(f"Not found in EpgUtil: {k}")

with open(r"F:\TVTEST PROJECT\TVTest-develop\src\EpgUtil.cpp", 'w', encoding='utf-8') as f:
    f.write(text)

print(f"EpgUtil.cpp updated: {cnt}/{len(replacements)}")
