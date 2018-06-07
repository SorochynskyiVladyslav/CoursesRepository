$(document).ready(() => {

    $('.delete-button').on('click', ()=>{
        let code = $(event.currentTarget).parent().siblings()[2].textContent;
        let xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
            if (this.readyState == 4) {
                let xhttp2 = new XMLHttpRequest();
                xhttp2.onreadystatechange = function() {
                    if (this.readyState == 4) {
                        update_table(JSON.parse(this.responseText));
                    }
                };
                xhttp2.open("GET", `/api/companies/all`, true);
                xhttp2.send();
            }
        };

        xhttp.open("GET", `/api/companies/delete/${code}`, true);
        xhttp.send();
    })

    $('.reference-button').on('click', ()=>{
        let code = $(event.currentTarget).parent().siblings()[2].textContent;
        add_reference(code);
    })

    $('#add_button').on('click', ()=>{
        $('.ui.small.modal')
            .modal('show');
    })
    $('#add_form').submit(()=>{
        add_company();
        $('.ui.small.modal')
            .modal('hide');
        event.preventDefault();
    });
    $('#search-form').submit(()=>{
        let search_query = $('#search-form').serialize();
        find_company(search_query);
        event.preventDefault();
    })

    $('#reference-status-button').on('click', ()=>{
        $('#reference-message').hide();
        $('#reference-status-form').show();
        $('#reference-modal')
            .modal('show');
    })
    $('#reference-status-form').submit(()=>{
        let search_query = $('#reference-status-form').serialize();
        reference_status(search_query);
        event.preventDefault();
    })


})

function generate_tr(company){
    let company_date = new Date(Date.parse(new String(company.date)));
    let date = company_date.getDate();
    let month = company_date.getMonth() + 1;
    let year = company_date.getFullYear();
    tr = `<tr class="company-tr">
        <td>${company.name}</td>
        <td>${company.address}</td>
        <td>${company.code}</td>
        <td>${date}.${month}.${year}</td>
        <td>${company.activity_type}</td>
        <td>${company.ownership_type}</td>
        <td><button class="ui button delete-button"><i class="red trash icon"></i></button></td>
        <td><a href="/edit_company/${company._id}"><button class="ui button edit-button"><i class="blue edit icon"></i></button></a></td>
      </tr>`;
    return tr;
}
function generate_user_tr(company){
    let company_date = new Date(Date.parse(new String(company.date)));
    let date = company_date.getDate();
    let month = company_date.getMonth() + 1;
    let year = company_date.getFullYear();
    tr = `<tr class="company-tr">
        <td>${company.name}</td>
        <td>${company.address}</td>
        <td>${company.code}</td>
        <td>${date}.${month}.${year}</td>
        <td>${company.activity_type}</td>
        <td>${company.ownership_type}</td>
        <td><button class="ui button reference-button"><i class="blue file icon"></i></button></td>
      </tr>`;
    return tr;
}

function update_table(companies){
    $('.company-tr').remove();
    for(let i=0; i < companies.length; i++){
        $('#companies-table').append(generate_tr(companies[i]));
    }
}
function update_table_modified(companies, user_owner) {
    $('.company-tr').remove();
    for(let i=0; i < companies.length; i++){
        if (user_owner) $('#companies-table').append(generate_tr(companies[i]));
        else $('#companies-table').append(generate_user_tr(companies[i]));
    }
}

function add_company(){
    let params = $('#add_form').serialize();
    let xhr = new XMLHttpRequest();
    xhr.open('POST', '/api/companies/add?' + params, true);
    xhr.onreadystatechange = function() {
        if (this.readyState == 4) {
            let xhr2 = new XMLHttpRequest();
            xhr2.onreadystatechange = function() {
                if (this.readyState == 4) {
                    update_table(JSON.parse(this.responseText));
                }
            };
            xhr2.open('GET', `/api/companies/all`, true);
            xhr2.send();
        }
    };
    xhr.send();
}
function find_company(search_query){
    let xhr = new XMLHttpRequest();
    if (search_query.length > 5){
        xhr.onreadystatechange = function () {
            if (this.readyState == 4) {
                if (this.responseText.length > 0) {
                    $('.company-tr').remove();
                    let user_owner = false;
                    if (JSON.parse(this.responseText).user && JSON.parse(this.responseText).user.status == 'owner')
                        user_owner = true;
                    let companies = [];
                    companies[0] = JSON.parse(this.responseText).company;
                    update_table_modified(companies, user_owner);
                }
                else {
                    $('#search-message').text('Пошук не дав жодних результатів. Перевірте правильність введеного ЄДРПОУ підприємства.');
                    $('#search-modal')
                        .modal('show');
                }
            }
        };
        xhr.open("GET", `/api/companies/find?${search_query}`, true);
        xhr.send();
    }
    else {
        $('#search-message').text('Поле для пошуку пусте. Введіть ЄДРПОУ підприємства для пошуку.');
        $('#search-modal')
            .modal('show');
    }
}

function add_reference(code){
    let xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
        if (this.readyState == 4) {
            let reference = JSON.parse(this.responseText);
            $('#reference-message').text(`Довідку для компанії за номером ЄДРПОУ ${reference.company_code} замовлено! ID для перевірки статусу довідки: ${reference._id}`);
            $('#reference-message').show();
            $('#reference-status-form').hide();
            $('#reference-modal')
                .modal('show');
        }
    };
    xhr.open("GET", `/api/references/add?code=${code}`, true);
    xhr.send();
}

function reference_status(search_query){
    let xhr = new XMLHttpRequest();
    if (search_query.length > 7) {
        xhr.onreadystatechange = function(){
            if (this.readyState == 4) {
                if (this.responseText.length > 0) {
                    let reference = JSON.parse(this.responseText);
                    $('#reference-message').text(`Статус довідки: ${reference.status}`);
                }
                else {
                    $('#reference-message').text('Довідки не знайдено. Перевірте правильність введеного ID довідки');
                }
                $('#reference-message').show();
            }
        };
        xhr.open("GET", `/api/references/find?${search_query}`, true);
        xhr.send();
    }
    else {
        $('#reference-message').text('Поле пошуку пусте. Введіть ID Довідки');
        $('#reference-message').show();
    }
}