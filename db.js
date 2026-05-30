// ════════════════════════════════════════
//  HOME HELPER — база данных пользователей
//
//  Хранится в памяти (без сервера).
//  Данные сбрасываются при перезагрузке.
//
//  Чтобы добавить пользователя заранее —
//  допиши объект в массив PRESET_USERS.
//
//  Тестовые аккаунты:
//    login: admin    password: admin123
//    login: test     password: test123
// ════════════════════════════════════════



const DB = (() => {

    function simpleHash(str) {
        let h = 5381;
        for (let i = 0; i < str.length; i++) h = (h * 33) ^ str.charCodeAt(i);
        return (h >>> 0).toString(36);
    }


    const PRESET_USERS = [
        { username: "admin", passwordHash: simpleHash("admin123") },
        { username: "test",  passwordHash: simpleHash("test123")  },
    ];

    let users       = [...PRESET_USERS];
    let currentUser = null;

    return {
        simpleHash,


        register(username, password, password2) {
            if (username.length < 3)    return "Логин должен быть не менее 3 символов.";
            if (password.length < 6)    return "Пароль должен быть не менее 6 символов.";
            if (password !== password2) return "Пароли не совпадают.";
            if (users.find(u => u.username.toLowerCase() === username.toLowerCase()))
                return "Такой логин уже занят.";
            users.push({ username, passwordHash: simpleHash(password) });
            currentUser = username;
            return null;
        },


        login(username, password) {
            const user = users.find(u => u.username.toLowerCase() === username.toLowerCase());
            if (!user)                                      return "Пользователь не найден.";
            if (user.passwordHash !== simpleHash(password)) return "Неверный пароль.";
            currentUser = user.username;
            return null;
        },

        logout() { currentUser = null; },

        getCurrentUser() { return currentUser; },

        getUserList() { return users.map(u => u.username); },
    };
})();