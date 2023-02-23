<!DOCTYPE html>
<html lang="ru">
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.1/dist/js/bootstrap.min.js" integrity="sha384-skAcpIdS7UcVUC05LJ9Dxay8AXcDYfBJqt1CJ85S/CFujBsIzCIv+l9liuYLaMQ/" crossorigin="anonymous"></script>
        <link rel="stylesheet" href="assets/css/main.css" />
        <link rel="stylesheet" href="assets/css/article.css" />
        <title>Регистрация</title>
    </head>
    <body>
        <header class="header">
            <nav class="navigation__wrapper">
                <div class="header__logo">
                    The Site
                </div>
                <ul class="navigation">
                    <li class="navigation__item">
                        <a href="article.html" class="navigation__link">
                        Статья
                        </a>
                    </li>
                    <li class="navigation__item">
                        <a href="notes.html" class="navigation__link">
                        Заметки
                        </a>
                    </li>
                    <li class="navigation__item">
                        <a href="statistics.html" class="navigation__link">
                        Статистика
                        </a>
                    </li>
                    <li class="navigation__item active">
                        <a href="registr.php" class="navigation__link">
                        Регистрация
                        </a>
                    </li>
                    <li class="navigation__item">
					<a href="API.html" class="navigation__link">
					Внешнее API
					</a>
				</li>
                </ul>
            </nav>
        </header>
        <form id="formm" method="post" enctype="multipart/form-data">
            <div class="col-sm-8 m-auto col-10">
                <h4 class="text-center">Регистрация нового пользователя</h4>
                <div class="row row-cols-1 row-cols-xxl-4  mt-2">
                    <div class=" col">
                        <label for="form_name"> Имя</label>
                        <input name="name1" type="text" class="form-control" pattern="[A-Za-zА-Яа-яЁё]+" placeholder="Введите имя" required>
                    </div>
                    <div class=" col">
                        <label for="form_name">Фамилия</label>
                        <input name="name2" type="text" class="form-control" pattern="[A-Za-zА-Яа-яЁё]+" placeholder="Введите фамилию" required>
                    </div>
                    <div class=" col">
                        <label for="form_name">Отчество</label>
                        <input name="name3" type="text" class="form-control" pattern="[A-Za-zА-Яа-яЁё]+" placeholder="Введите отчество (если есть)">
                    </div>
                    <div class=" col">
                        <label for="form_name">Дата рождения</label >
                        <input name="date" type="date" class="form-control" required>
                    </div>
                </div>
                <div class="row row-cols-1 row-cols-xxl-3  mt-2">
                    <div class=" col">
                        <label for="form_name">Email</label>
                        <input name="email" type="email" class="form-control" placeholder="example@mail.ru" required>
                    </div>
                    <div class=" col">
                        <label for="form_name">Пароль</label>
                        <input name="password" type="password" class="form-control" placeholder="Введите пароль" id="Passwordd1" required>
                    </div>
                    <div class=" col">
                        <label for="form_name">Повторите пароль</label>
                        <input type="password" class="form-control" placeholder="Введите пароль" id="Passwordd2" required>
                    </div>
                </div>
                <div class="row mt-2">
                    <div class=" col">
                        <label for="form_name">Страна</label>
                        <input name="country" class="form-control" list="datalistOptions" id="exampleDataList" placeholder="Введите название страны" required>
                        <datalist id="datalistOptions">
                            <option value="Азербайджанская Республика">
                            <option value="Республика Армения">
                            <option value="Республика Беларусь">
                            <option value="Республика Казахстан">
                            <option value="Кыргызская Республика">
                            <option value="Республика Молдова">
                            <option value="Российская Федерация">
                            <option value="Республика Таджикистан">
                            <option value="Туркменистан">
                            <option value="Республика Узбекистан">
                            <option value="Украина">
                        </datalist>
                    </div>
                </div>
                <div class="row row-cols-1 row-cols-xxl-2  mt-2">
					<div class=" col">
						<label for="form_name">Выберите роль</label>
						<select name="role" class="form-select" aria-label="Default select example">
							<option selected>Выберите..</option>
							<option value="1">Пользователь</option>
							<option value="2">Администратор</option>
							<option value="3">Гость</option>
						</select>
					</div>
					<div class=" col">
						<label for="form_name">Выберите репутацию</label>
						<input name="rate" type="number" class="form-control" placeholder="от 1 до 5" min="1" max="5" step="1" required>
					</div>
                </div>
                <div class="row row-cols-1 row-cols-xxl-2  mt-2">
                    <div class=" col">
                        <label for="form_name">Выберите пол:</label>
                        <div class="form-check form-check-inline">
                            <input name="sex" class="form-check-input" type="radio" id="flexRadioDefault1" value="man"checked >
                            <label class="form-check-label" for="flexRadioDefault1">
                            Мужской
                            </label>
                        </div>
                        <div class="form-check form-check-inline">
                            <input name="sex" class="form-check-input" type="radio" id="flexRadioDefault2" value="woman">
                            <label class="form-check-label" for="flexRadioDefault2">
                            Женский
                            </label>
                        </div>
                        <div class="form-check form-check-inline">
                            <input name="sex" class="form-check-input" type="radio" id="flexRadioDefault3" value="unknown">
                            <label class="form-check-label" for="flexRadioDefault3">
                            Не определить
                            </label>
                        </div>
                    </div>
				</div>
                    <div class="row row-cols-1 row-cols-xxl-3  mt-2">
                        <div class=" col">
                            <label for="form_name">Добавить аватар</label>
							<input type="hidden" name="MAX_FILE_SIZE" value="83886080" />
                            <input name="picture" type="file" class="form-control" placeholder="example@mail.ru" required>
                        </div>
                    </div>
                    <div class="row row-cols-1  mt-2">
                        <div class=" col">
                            <label for="form_name">Расскажите о себе</label>
                            <textarea name="text" class="form-control" id="exampleFormControlTextarea1" rows="5" required></textarea>
                        </div>
                    </div>
                    <div class="row mt-2">
                        <div class=" col">
                            <div class="form-check">
                                <input name="check1" class="form-check-input" type="checkbox" value="ON" id="flexCheckDefault" required>
                                Я согласен(-на) с обработкой персональных данных
                                </label>
                            </div>
                            <div class="form-check">
                                <input name="check2" class="form-check-input" type="checkbox" value="ON" id="flexCheckDefault" required>
                                Я согласен(-на) с получением писем об обновлениях
                                </label>
                            </div>
                        </div>
                    </div>
                    <button type="submit" class="btn btn-primary mt-2">Отправить</button>
                    <button type="reset" class="btn btn-primary mt-2">Очистить</button>
					<div class="row row-cols-1 mt-2">		
					<?php
					if (count($_POST)>0)
						{
							$uploaddir = 'uploads/';
							if ($_FILES['picture']['error'] == UPLOAD_ERR_OK) 
								{
									$uploadfile = $uploaddir.basename($_FILES['picture']['name']);
									move_uploaded_file($_FILES['picture']['tmp_name'], $uploadfile);
									echo "<div class= col ><img src=$uploadfile></div>";
								}
							$uploadres=$uploaddir.'resdata.txt';
							file_put_contents($uploadres, json_encode(array_merge($_POST, $_FILES)));	
							echo "<div class= col ><a href='$uploadres'> Сcылка на файл</a></div>";
						}
					?>
					</div>
            </div>
        </form>
        <script>
            formm.oninput = function(){
               Passwordd2.setCustomValidity(Passwordd2.value != Passwordd1.value ? (Passwordd2.value == "" ? "Заполните это поле.": "Пароли не совпадают.") : "")
            	}
        </script>
        <footer class="footer">
            <p class="footer__copyrights">© Copyrights 2021</p>
        </footer>
        <script type="text/javascript" src="src/article.js"></script>
    </body>
</html>